/*
 * Door.cpp - A door...
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

#include <Door.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_Door(IOObjectSystem* obj_sys)
{
	return (COObject*)new Door(obj_sys);
}
}

Door::Door(IOObjectSystem* obj_sys)
: Pawn(obj_sys)
{

};

Door::~Door()
{

};

bool Door::isAttackable()
{
	return true;
};

bool Door::isAutoAttackable()
{
	return true;
};

irr::f64 Door::getMaxHp()
{
	return 10;
};

irr::f64 Door::getHp()
{
	return 0;
};

// Setters
void Door::setHp(irr::f64 hp)
{

};

// Events
void Door::onBeenSeen(Actor* obj)
{

};

void Door::onBeenLost(Actor* obj)
{

};

void Door::onClick(COObject* event_instagator, bool shift_click)
{

};

void Door::onDeath(Actor* event_instagator)
{

};

void Door::takeDamage(Actor* event_instagator, irr::u32 &damage, bool crit, bool shield)
{

};

}
}
