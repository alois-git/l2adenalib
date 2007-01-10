/*
 * CPCharSelected.h - Sent once char in game.
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

#ifndef _ADENA_C_P_CHAR_SELECTED_H_
#define _ADENA_C_P_CHAR_SELECTED_H_

#include <CPacket.h>
#include <COPlayer.h>

namespace adena
{
namespace game_server
{

	class CPCharSelected : public CPacket
	{
	public:

		CPCharSelected(COPlayer* player)
		: CPacket()
		{
			w8(0x15);

			wStrW(player->Name); // Name
			w32(0x00); // Char object id
			wStrW(irr::core::stringc("OMG I R TEH NUB")); // Title
			w32(0x00); // session id (why do we send this so many times?)
			w32(0x00); // Clan id
			w32(0x00);
			w32(0x00); // Sex
			w32(0x00); // Race
			w32(0x00); // Class
			w32(0x01);
			w32(-71338); // x
			w32(258271); // y
			w32(-3104); // z

			wf(0x00); // Current hp
			wf(0x00); // Current mp
			w32(0x00); // Current sp
			w64(0x00); // Current xp
			w32(80); // Current lvl
			w32(0x00); // Current karma
			w32(0x0);
			w32(0x00); // INT
			w32(0x00); // STR
			w32(0x00); // CON
			w32(0x00); // MEN
			w32(0x00); // DEX
			w32(0x00); // WIT

			for(irr::u32 i = 0; i < 30; i++)
			{
				w32(0x00);
			}

            w32(0x00);
            w32(0x00);
			w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x00);
		};

		virtual ~CPCharSelected()
		{

		};

		virtual irr::c8* getData()
		{
			return Data;
		};

		virtual irr::u32 getLen()
		{
			return WritePointer;
		};

	private:



	};

}
}

#endif
