/*
 * Door.h - A door...
 * Created February 10, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_O_DOOR_H_
#define _ADENA_C_O_DOOR_H_

#include <Pawn.h>

namespace adena
{
namespace game_server
{

	class Door : public Pawn
	{
	public:

		Door(IOObjectSystem* obj_sys);

		virtual ~Door();

		// Getters
		virtual bool isAttackable();
		virtual bool isAutoAttackable();

		virtual irr::f64 getMaxHp();
		virtual irr::f64 getHp();

		// Setters
		virtual void setHp(irr::f64 hp);

		// Events
		virtual void onBeenSeen(Actor* obj);
		virtual void onBeenLost(Actor* obj);

		virtual void onClick(COObject* event_instagator, bool shift_click);

		virtual void onDeath(Actor* event_instagator);

		virtual void takeDamage(Actor* event_instagator, irr::u32 &damage, bool crit, bool shield);
	};

}
}

#endif
