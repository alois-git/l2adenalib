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
#include <CSPNpcInfo.h>
#include <CSPDeleteObj.h>

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
: Pawn(obj_sys)
{

};

NPC::~NPC()
{

};

void NPC::respawn()
{
	Location = SpawnLoc;
	Heading = SpawnHeading;
};

void NPC::onSeeObj(Actor* obj)
{
	
};

void NPC::onBeenSeen(Actor* obj)
{
	Player* p = dynamic_cast<Player*>(obj);
	if(p)
	{
		CSPNpcInfo* ni = new CSPNpcInfo(this);
		p->Owner->sendPacket(ni);
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

}
}
