/*
 * COPlayer.h - A player.
 * Created January 8, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_O_PLAYER_H_
#define _ADENA_C_O_PLAYER_H_

#include <COPawn.h>
#include <irrString.h>
#include <SCharInfo.h>
#include <CGameServerClient.h>

namespace adena
{
namespace game_server
{

	irr::f64 _inline getConMod(irr::u32 con);
	irr::f64 _fastcall getBaseHpForClass(irr::u32 class_id, irr::u32 level);

	class COPlayer : public COPawn
	{
	public:

		COPlayer(IGameServerClient* client);

		virtual ~COPlayer() {}

		virtual irr::u32 getLevel();

		virtual irr::u32 getStr();
		virtual irr::u32 getCon();
		virtual irr::u32 getDex();
		virtual irr::u32 getInt();
		virtual irr::u32 getWit();
		virtual irr::u32 getMen();

		virtual irr::u32 getHp();

		virtual irr::u32 getMaxHp();

		virtual irr::u32 getMp();

		virtual irr::u32 getMaxMp();

		SCharInfo* CharInfo;
		IGameServerClient* Client;

	protected:

	};

}
}

#endif
