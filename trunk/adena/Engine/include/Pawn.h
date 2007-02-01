/*
 * Pawn.h - Base class for any moving object in the game.
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

#ifndef _ADENA_O_PAWN_H_
#define _ADENA_O_PAWN_H_

#include <Actor.h>
#include <IGameServerClient.h>

namespace adena
{
namespace game_server
{

	enum E_MoveState
	{
		EMS_Still = 0,
		EMS_Moving,
		EMS_RequestMove
	};

	class Pawn : public Actor
	{
	public:

		Pawn(IOObjectSystem* obj_sys);

		virtual ~Pawn();

		virtual void destroy();

		virtual void tick(irr::f32 delta_time);

		virtual irr::u32 getSpeed();

		virtual irr::u32 getLevel();

		virtual irr::u32 getMaxHp();
		virtual irr::u32 getHp();
		virtual irr::u32 getMaxMp();
		virtual irr::u32 getMp();
		virtual irr::u32 getMaxCp();
		virtual irr::u32 getCp();

		virtual irr::u32 getSTR();
		virtual irr::u32 getCON();
		virtual irr::u32 getDEX();
		virtual irr::u32 getINT();
		virtual irr::u32 getWIT();
		virtual irr::u32 getMEN();

		virtual void moveToLocation(irr::core::vector3df Target);

		//virtual void teleportToLocation(irr::core::vector3di Target);

		virtual void attack(Actor* target, bool shift_click);

		// Event called when MoveTarget reached.
		virtual void onStopMove();

		virtual void onClick(COObject* event_instagator, bool shift_click);

		irr::core::vector3df MoveTarget;
		E_MoveState MoveState;
		// We don't need to check our height EVERY tick...
		irr::u32 LastZCheck;

		IGameServerClient* Owner;

	};

}
}

#endif
