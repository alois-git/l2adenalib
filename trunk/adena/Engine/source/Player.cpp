/*
 * Player.cpp - Base class for a player.
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

#include <Player.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_Player(IOObjectSystem* obj_sys)
{
	return (COObject*)new Player(obj_sys);
}
}

Player::Player(IOObjectSystem* obj_sys)
: Pawn(obj_sys)
{

};

Player::~Player()
{

};

void Player::destroy()
{
	saveToDatabase();
	CharInfo->InUse = false;
	Pawn::destroy();
};

irr::u32 Player::getSpeed()
{
	SClassTemplate* ct = Owner->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->RUN_SPEED;
};

void Player::saveToDatabase()
{
	CharInfo->x = Location.X;
	CharInfo->y = Location.Y;
	CharInfo->z = Location.Z;
	Owner->Server->Interfaces.PlayerCache->saveChar(CharInfo->CharacterId);
};

}
}
