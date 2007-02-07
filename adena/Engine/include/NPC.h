/*
 * NPC.h - An npc.
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

#ifndef _ADENA_C_O_NPC_H_
#define _ADENA_C_O_NPC_H_

#include <Pawn.h>

namespace adena
{
namespace game_server
{

	class NPC : public Pawn
	{
	public:

		NPC(IOObjectSystem* obj_sys);

		virtual ~NPC();

		virtual void respawn();

		virtual void onSeeObj(Actor* obj);

		virtual void onBeenSeen(Actor* obj);

		virtual void onLoseObj(Actor* obj);

		virtual void onBeenLost(Actor* obj);

		irr::core::vector3df SpawnLoc;
		irr::u32 RespawnDelay;
		irr::s32 SpawnHeading;

		SNPCInfo* NPCInfo;
	};

}
}

#endif
