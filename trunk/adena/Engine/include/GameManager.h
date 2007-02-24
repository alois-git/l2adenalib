/*
 * GameManager.h - Basicly manages the game play of the server.
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

#ifndef _ADENA_C_O_GAME_MANAGER_H_
#define _ADENA_C_O_GAME_MANAGER_H_

#include <COObject.h>
#include <Player.h>
#include <World.h>
#include <IGameServerClient.h>
#include <SCharInfo.h>
#include <irrList.h>
#include <IPacket.h>
#include <Mutator.h>

namespace adena
{
namespace game_server
{

	class GameManager : public COObject
	{
	public:

		GameManager(IOObjectSystem* obj_sys);

		virtual ~GameManager();

		virtual void init(SGameServerInterfaces* interfaces);

		virtual void tick(irr::f32 delta_time);

		virtual void broadcastPacket(IPacket* packet);

		virtual Player* playerEnterWorld(SCharInfo* char_info, IGameServerClient* owner);

		virtual void playerLeaveWorld(Player* player);

		irr::core::list<Player*> PlayerList;

		irr::core::stringc ControllerClass;
		// A subclass of Player (ex. Engine.L2Player).
		irr::core::stringc PlayerClass;
		// Default NPC class to use. (ex. Engine.L2NPC).
		irr::core::stringc NpcClass;

		World* L2World;
		SGameServerInterfaces* Interfaces;
		Mutator* Mut;

	};

}
}

#endif
