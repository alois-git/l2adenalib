/*
 * GameManager.cpp - Basicly manages the game play of the server.
 * Created January 25, 2007, by Michael 'Bigcheese' Spencer.
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

#include <GameManager.h>
#include <Controller.h>
#include <CPCharInfo.h>
#include <CSPSystemMessage.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_GameManager(IOObjectSystem* obj_sys)
{
	return (COObject*)new GameManager(obj_sys);
}
}

GameManager::GameManager(IOObjectSystem* obj_sys)
: COObject(obj_sys)
{
	ControllerClass = "Engine.Controller";
	PlayerClass = "Engine.Player";
};

GameManager::~GameManager()
{

};

void GameManager::tick(irr::f32 delta_time)
{

};

void GameManager::broadcastPacket(IPacket* packet)
{
	packet->getRef();
	irr::core::list<Player*>::Iterator ittr(PlayerList.begin());
	for(; ittr != PlayerList.end(); ittr++)
	{
		(*ittr)->Owner->sendPacket(packet);
	}
	packet->drop();
};

Player* GameManager::playerEnterWorld(SCharInfo* char_info, IGameServerClient* owner)
{
	Controller* c = (Controller*)spawn(ControllerClass);
	owner->PController = c;
	c->Owner = owner;
	Player* p = (Player*)spawn(PlayerClass);
	p->Owner = owner;
	p->CharInfo = owner->CharInfo;
	p->Location.X = p->CharInfo->x;
	p->Location.Y = p->CharInfo->y;
	p->Location.Z = p->CharInfo->z;
	p->Location.Z = owner->Server->Interfaces.GeoData->getHeight(p->Location);
	PlayerList.push_back(p);
	c->posses(p);
	char_info->InUse = true;
	CSPSystemMessage* sm = new CSPSystemMessage(irr::core::stringc("Welcome to l2adena - v") + ADENA_VERSION);
	owner->sendPacket(sm);

	CPCharInfo* ci = new CPCharInfo(p);
	ci->getRef();
	irr::core::list<Player*>::Iterator ittr(PlayerList.begin());
	for(; ittr != PlayerList.end(); ittr++)
	{
		if((*ittr) != p)
		{
			(*ittr)->Owner->sendPacket(ci);
			owner->sendPacket(new CPCharInfo((*ittr)));
		}
	}
	ci->drop();

	return p;
};

void GameManager::playerLeaveWorld(Player* player)
{
	irr::core::list<Player*>::Iterator ittr(PlayerList.begin());
	for(; ittr != PlayerList.end(); ittr++)
	{
		if(player == (*ittr))
		{
			PlayerList.erase(ittr);
			player->destroy();
			break;
		}
	}
};

}
}
