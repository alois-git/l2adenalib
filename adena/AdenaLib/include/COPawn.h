/*
 * COPawn.h - A base pawn.
 * Created January 7, 2007, by Michael 'Bigcheese' Spencer.
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

/*
 * A pawn can be anything from an player to a NPC (ELPY FTW!!!)
 */

#ifndef _ADENA_C_O_PAWN_H_
#define _ADENA_C_O_PAWN_H_

#include <COActor.h>

namespace adena
{
namespace game_server
{

	class COPawn
	{
	public:

		COPawn() {}

		virtual ~COPawn() {}

		virtual irr::u32 getLevel() = 0;

		virtual irr::u32 getStr() = 0;
		virtual irr::u32 getCon() = 0;
		virtual irr::u32 getDex() = 0;
		virtual irr::u32 getInt() = 0;
		virtual irr::u32 getWit() = 0;
		virtual irr::u32 getMen() = 0;

		virtual irr::u32 getHp() = 0;

		virtual irr::u32 getMaxHp() = 0;

		virtual irr::u32 getMp() = 0;

		virtual irr::u32 getMaxMp() = 0;

	private:

	};

}
}

#endif
