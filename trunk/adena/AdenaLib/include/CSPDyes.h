/*
 * CSPDyes.h - Send the client their dye info.
 * Created January 12, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_DYES_H_
#define _ADENA_C_S_P_DYES_H_

#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CSPDyes : public CServerPacket
	{
	public:

		CSPDyes()
		: CServerPacket()
		{

		};

		virtual ~CSPDyes() {};

		virtual bool writePacket()
		{
			w8(0xe4);

			w8(0x00); //equip INT
			w8(0x00); // Equip STR
			w8(0x00); // Equip CON
			w8(0x00); // Equip MEM
			w8(0x00); // Equip DEX
			w8(0x00); // Equip WIT

			w32(0x03);
			irr::u32 i;
			for(i = 0; i < 3; i++)
			{
				w32(0x03);
				w32(0x00); // Dye id
			}

			return true;
		};

		virtual irr::c8* getData()
		{
			return Data;
		};

		virtual irr::u32 getLen()
		{
			return WritePointer;
		};

	};

}
}

#endif
