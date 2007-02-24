/*
 * Pawn.cpp - Base class for any moving object in the game.
 * Created January 26, 2007, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Michael Spencer - bigcheesegs@gmail.com
 */

#include <Pawn.h>
#include <Player.h>
#include <CSPStopMove.h>
#include <CSPDeleteObj.h>
#include <CSPMoveToLocation.h>
#include <CSPStatusUpdate.h>
#include <GameManager.h>
#include <Controller.h>
#include <CSPAttack.h>
#include <CSPSystemMessage.h>
#include <CSPDie.h>
#include <CSPSkillLaunched.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_Pawn(IOObjectSystem* obj_sys)
{
	return (COObject*)new Pawn(obj_sys);
}
}

Pawn::Pawn(IOObjectSystem* obj_sys)
: Actor(obj_sys), Owner(0), MoveState(EMS_Still), PawnState(EPS_None), Target(0), HpUpdated(false), CpUpdated(false), Cp(0), Hp(0), Mp(0)
{

};

Pawn::~Pawn()
{

};

void Pawn::destroy()
{
	broadcastPacket(new CSPDeleteObj(Id));
	Actor::destroy();
};

void Pawn::tick(irr::f32 delta_time)
{
	Actor::tick(delta_time);
	if(MoveState == EMS_Moving || MoveState == EMS_Walking)
	{
		irr::u32 speed = getSpeed();
		irr::core::line3df line(Location, MoveTarget);
		irr::core::vector3df heading = line.getVector();
		heading.setLength(delta_time * speed);
		irr::core::vector3df newloc = Location + heading;
		if(MoveTarget.isBetweenPoints(Location, newloc))
		{
			// We have reached our target.
			MoveState = EMS_Still;
			Location = MoveTarget;
			onStopMove();
			LastZCheck = 0; // Force z check on stop
		}else
		{
			Location = newloc;
		}

		irr::u32 time = irr::os::Timer::getRealTime();
		if((time - LastZCheck) >= 1000) // Check every second
		{
			//Location.Z = Owner->Server->Interfaces.GeoData->getHeight(Location);
			LastZCheck = time;
			GameManager* gm = dynamic_cast<GameManager*>(Owner->Server->Interfaces.GameManager);
			if(gm)
			{
				gm->L2World->updateLoc(this);
			}
		}
	}
	if(HpUpdated || CpUpdated)
	{
		broadcastPacket(new CSPStatusUpdate(this));
	}
};

irr::u32 Pawn::getSpeed()
{
	return 0;
};

irr::u32 Pawn::getLevel()
{
	return 0;
};

irr::f64 Pawn::getMaxHp()
{
	return 0;	
};

irr::f64 Pawn::getHp()
{
	return 0;
};

irr::f64 Pawn::getMaxMp()
{
	return 0;
};

irr::f64 Pawn::getMp()
{
	return 0;	
};

irr::f64 Pawn::getMaxCp()
{
	return 0;
};

irr::f64 Pawn::getCp()
{
	return 0;
};

irr::u32 Pawn::getSTR()
{
	return 0;
};

irr::u32 Pawn::getCON()
{
	return 0;
};

irr::u32 Pawn::getDEX()
{
	return 0;
};

irr::u32 Pawn::getINT()
{
	return 0;
};

irr::u32 Pawn::getWIT()
{
	return 0;
};

irr::u32 Pawn::getMEN()
{
	return 0;
};

bool Pawn::isAutoAttackable()
{
	return false;
};

bool Pawn::isDead()
{
	if(PawnState == EPS_Dead)
		return true;
	return false;
};

bool Pawn::isLooksDead()
{
	return isDead();
};

void Pawn::moveToLocation(irr::core::vector3df Target)
{
	if(PawnState == EPS_Dead)
		return;
	if(PawnState == EPS_Attacking || PawnState == EPS_Casting)
		PawnState = EPS_None;
	MoveTarget = Owner->Server->Interfaces.GeoData->moveCheck(Location, Target);
	broadcastPacket(new CSPMoveToLocation(Id, MoveTarget, Location));
	MoveState = EMS_Moving;
};

void Pawn::attack(Actor* target, bool shift_click)
{
	if(PawnState != EPS_None)
	{
		return;
	}

	if(MoveState == EMS_Sitting)
	{
		return;
	}

	Pawn* p = dynamic_cast<Pawn*>(target);
	if(p)
		if(p->PawnState == EPS_Dead)
			return;

	if(MoveState != EMS_Still)
	{
		// We need to stop before we can attack
		moveToLocation(Location);
	}
	PawnState = EPS_Attacking;
	CSPAttack* a = new CSPAttack(this);
	a->addHit(target, 1, false, false, false);
	broadcastPacket(a);
	irr::f32 atkspd = getAttackSpeed();
	irr::u32 time = 460000/atkspd;
	ObjectSystem->regTimerFunc(this, (IOObjectSystem::timerFunc)&Pawn::attackTimer, time, (void*)target);
};

void Pawn::useSkill(irr::u32 skill_id, bool ctrl, bool shift)
{

};

void Pawn::takeDamage(Actor* event_instagator, irr::u32 &damage, bool crit, bool shield)
{
	if(PawnState != EPS_Dead)
	{
		Tick = true;
		if(damage < Cp)
		{
			setCp(Cp - damage);
		}else
		{
			damage -= Cp;
			setCp(0);
			setHp(getHp() - damage);
			if(Hp <= 0)
			{
				onDeath(event_instagator);
			}
		}
	}
};

bool Pawn::attackTimer(void* data)
{
	if(PawnState == EPS_Attacking)
		onDoAttackDmg((Actor*)data);
	return false;
};

bool Pawn::skillTimer(void* data)
{
	if(PawnState == EPS_Casting)
	{
		SSkill* s = (SSkill*)data;
		CSPSkillLaunched* sl = new CSPSkillLaunched(this, *s);
		broadcastPacket(sl);
		irr::u32 dmg = getMAttack();
		Target->takeDamage(this, dmg, false, false);
	}
	return false;
};

irr::u32 Pawn::onDoAttackDmg(Actor* target)
{
	if(PawnState == EPS_Attacking)
	{
		// Calculate damage
		irr::u32 dmg = getPAttack() * 25;
		target->takeDamage(this, dmg, false, false);
		PawnState = EPS_None;
		return dmg;
	}
	return 0;
};

void Pawn::onDeath(Actor* event_instagator)
{
	if(MoveState == EMS_Moving || MoveState == EMS_Walking)
		moveToLocation(Location);
	PawnState = EPS_Dead;
	broadcastPacket(new CSPDie(this));
	Player* p = dynamic_cast<Player*>(event_instagator);
	if(p)
	{
		((Controller*)p->Owner->PController)->setIntention(ECI_None);
	}
};

void Pawn::onStopMove()
{
	broadcastPacket(new CSPStopMove(Id, Location, Heading));
	if(Owner)
		((Controller*)Owner->PController)->checkIntention();
};

void Pawn::onClick(COObject* event_instagator, bool shift_click)
{
	Controller* c = dynamic_cast<Controller*>(event_instagator);
	if(c)
	{
		if(c->Target == this)
		{
			// If auto attackable, start attacking
		}else
		{
			c->setTarget(this);
		}
	}
};

}
}
