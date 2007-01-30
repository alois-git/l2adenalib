/*
 * Player.h - Base class for a player.
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

#ifndef _ADENA_O_PLAYER_H_
#define _ADENA_O_PLAYER_H_

#include <Pawn.h>
#include <SCharInfo.h>

namespace adena
{
namespace game_server
{

	class Player : public Pawn
	{
	public:

		Player(IOObjectSystem* obj_sys);

		virtual ~Player();

		virtual void destroy();

		virtual irr::u32 getSpeed();

		virtual void saveToDatabase();

		SCharInfo* CharInfo;

	};

}
}

#endif
