/*
 * NPC.cpp - An npc.
 * Created February 6, 2007, by Michael 'Bigcheese' Spencer.
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

#include <NPC.h>
#include <Player.h>
#include <Controller.h>
#include <ItemOnGround.h>
#include <GameManager.h>
#include <CSPNpcInfo.h>
#include <CSPDeleteObj.h>
#include <CSPStatusUpdate.h>
#include <CSPSystemMessage.h>
#include <CDbRandInstance.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_NPC(IOObjectSystem* obj_sys)
{
	return (COObject*)new NPC(obj_sys);
}
}

NPC::NPC(IOObjectSystem* obj_sys)
: Pawn(obj_sys), TickingHpMp(false)
{
	//ObjectSystem->regTimerFunc(this, (IOObjectSystem::timerFunc)&NPC::regenHpMpCp, 5000);
};

NPC::~NPC()
{

};

bool NPC::isAttackable()
{
	return true;
};

bool NPC::isAutoAttackable()
{
	if(NPCInfo->SpawnClass == "L2Monster")
		return true;
	return false;
};

irr::f64 NPC::getMaxHp()
{
	return NPCInfo->Hp;
};

irr::f64 NPC::getHp()
{
	return Hp;
};

irr::f64 NPC::getMaxMp()
{
	return NPCInfo->Mp;
};

irr::f64 NPC::getMp()
{
	return Mp;
};

irr::f32 NPC::getHpRegen()
{
	return NPCInfo->Hp_regen;
};

irr::f32 NPC::getMpRegen()
{
	return NPCInfo->Mp_regen;
};

void NPC::setHp(irr::f64 hp)
{
	irr::f64 maxhp = getMaxHp();
	if(hp > maxhp)
		hp = maxhp;
	else if(hp < 0)
		hp = 0;
	if(Hp != hp)
	{
		Hp = hp;
		HpUpdated = true;
	}
};

void NPC::setMp(irr::f64 mp)
{
	irr::f64 maxmp = getMaxMp();
	if(mp > maxmp)
		mp = maxmp;
	else if(mp < 0)
		mp = 0;
	Mp = mp;
	// Client doesn't care about the NPCs mp.
};

void NPC::respawn()
{
	Location = SpawnLoc;
	Heading = SpawnHeading;
	Hp = NPCInfo->Hp;
	Mp = NPCInfo->Mp;
	PawnState = EPS_None;
};

void NPC::onSeeObj(Actor* obj)
{
	
};

void NPC::onBeenSeen(Actor* obj)
{
	if(PawnState != EPS_Dead)
	{
		Player* p = dynamic_cast<Player*>(obj);
		if(p)
		{
			CSPNpcInfo* ni = new CSPNpcInfo(this);
			p->Owner->sendPacket(ni);
			//Tick = true;
		}
	}
};

void NPC::onLoseObj(Actor* obj)
{
	
};

void NPC::onBeenLost(Actor* obj)
{
	Player* p = dynamic_cast<Player*>(obj);
	if(p)
	{
		CSPDeleteObj* ni = new CSPDeleteObj(Id);
		p->Owner->sendPacket(ni);
	}
};

void NPC::onClick(COObject* event_instagator, bool shift_click)
{
	Controller* c = dynamic_cast<Controller*>(event_instagator);
	if(c)
	{
		if(c->Target == this)
		{
			// If auto attackable, start attacking
			if(isAutoAttackable())
			{
				c->requestAttack(c->Target, shift_click);
			}
		}else
		{
			CSPStatusUpdate* si = new CSPStatusUpdate(this);
			si->forceUpdate(ESI_CUR_HP);
			si->forceUpdate(ESI_MAX_HP);
			c->Owner->sendPacket(si);
			c->setTarget(this);
		}
	}
};

void NPC::onDeath(Actor* event_instagator)
{
	Pawn::onDeath(event_instagator);
	Player* p = dynamic_cast<Player*>(event_instagator);
	if(p)
	{
		irr::u32 xp = NPCInfo->Exp * p->Owner->Server->Interfaces.ConfigFile->getInt("gameserver", "xp_rate");
		irr::u32 sp = NPCInfo->Sp * p->Owner->Server->Interfaces.ConfigFile->getInt("gameserver", "sp_rate");
		p->setXpSp(p->Xp + xp, p->Sp + sp);
		CSPSystemMessage* sm = new CSPSystemMessage(EMI_YOU_EARNED_S1_EXP_AND_S2_SP);
		sm->addNumber(xp);
		sm->addNumber(sp);
		p->Owner->sendPacket(sm);
	}
	ObjectSystem->regTimerFunc(this, (IOObjectSystem::timerFunc)&NPC::disapearTimer, RespawnDelay * 900);
	ObjectSystem->regTimerFunc(this, (IOObjectSystem::timerFunc)&NPC::respawnTimer, RespawnDelay * 1000);

	// Drop items
	irr::IRng* rng = CDbRandInstance::getRngInstance();
	CConfig* c = CConfig::getInstance();
	CItemCache* ic = CItemCache::getInstance();
	GameManager* gm = (GameManager*)CGameServer::getGMInstance();
	for(irr::u32 i = 0; i < NPCInfo->DropInfo.size(); i++)
	{
		irr::u32 rand = rng->getRandS32(0, 1000000);
		if(rand <= (NPCInfo->DropInfo[i].Chance * c->getInt("gameserver", "drop_rate")))
		{
			// Create the item
			irr::s32 count = rng->getRandS32(NPCInfo->DropInfo[i].Min, NPCInfo->DropInfo[i].Max);

			ItemOnGround* iog = (ItemOnGround*)COObject::spawn("Engine.ItemOnGround");
			iog->Dropper = this;
			iog->ItemInfo = ic->getItemInfo(NPCInfo->DropInfo[i].ItemId);
			iog->Location = Location + irr::core::vector3df(rng->getRandS32(-35, 35), rng->getRandS32(-35, 35), rng->getRandS32(-35, 35));
			iog->ItemCount = count;

			gm->L2World->newObj(iog);
		}
	};

	Tick = false;
};

void NPC::takeDamage(Actor* event_instagator, irr::u32 &damage, bool crit, bool shield)
{
	Pawn::takeDamage(event_instagator, damage, crit, shield);
	if(!TickingHpMp)
	{
		ObjectSystem->regTimerFunc(this, (IOObjectSystem::timerFunc)&NPC::regenHpMpCp, 5000);
		TickingHpMp = true;
	}

};

bool NPC::regenHpMpCp(void *data)
{
	if(Hp == getMaxHp() && Mp == getMaxMp())
	{
		TickingHpMp = false;
		return false;
	}
	if(PawnState != EPS_Dead)
	{
		setHp(getHp() + getHpRegen());
		setMp(getMp() + getMpRegen());
	}
	return true;
};

bool NPC::disapearTimer(void* data)
{
	broadcastPacket(new CSPDeleteObj(Id));
	return false;
};

bool NPC::respawnTimer(void* data)
{
	respawn();
	broadcastPacket(new CSPNpcInfo(this));
	return false;
};

}
}
