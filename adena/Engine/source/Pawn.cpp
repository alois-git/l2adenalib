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
#include <CSPStopMove.h>
#include <CSPTargetSelected.h>
#include <CSPDeleteObj.h>
#include <CSPMoveToLocation.h>
#include <GameManager.h>
#include <Controller.h>
#include <CSPAttack.h>

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
: Actor(obj_sys), MoveState(EMS_Still), Target(0)
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
	if(MoveState == EMS_Moving)
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
			Location.Z = Owner->Server->Interfaces.GeoData->getHeight(Location);
			LastZCheck = time;
			GameManager* gm = dynamic_cast<GameManager*>(Owner->Server->Interfaces.GameManager);
			if(gm)
			{
				gm->L2World->updateLoc(this);
			}
		}
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

irr::u32 Pawn::getMaxHp()
{
	return 0;	
};

irr::u32 Pawn::getHp()
{
	return 0;
};

irr::u32 Pawn::getMaxMp()
{
	return 0;
};

irr::u32 Pawn::getMp()
{
	return 0;	
};

irr::u32 Pawn::getMaxCp()
{
	return 0;
};

irr::u32 Pawn::getCp()
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

void Pawn::moveToLocation(irr::core::vector3df Target)
{
	MoveTarget = Owner->Server->Interfaces.GeoData->moveCheck(Location, Target);
	broadcastPacket(new CSPMoveToLocation(Id, MoveTarget, Location));
	MoveState = EMS_Moving;
};

void Pawn::attack(Actor* target, bool shift_click)
{
	CSPAttack* a = new CSPAttack(this);
	a->addHit(target, 1, false, false, false);
	broadcastPacket(a);
};

void Pawn::useSkill(irr::u32 skill_id, bool ctrl, bool shift)
{

};

void Pawn::onStopMove()
{
	broadcastPacket(new CSPStopMove(Id, Location, Heading));
};

void Pawn::onClick(COObject* event_instagator, bool shift_click)
{
	// We have been targeted, tell everyone about it.
	Controller* c = dynamic_cast<Controller*>(event_instagator);
	if(c)
	{
		c->Target = this;
		broadcastPacket(new CSPTargetSelected(c->OwnedPawn->Id, Id, Location));
	}
};

}
}
