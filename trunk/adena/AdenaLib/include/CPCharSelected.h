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

#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CPCharSelected : public CServerPacket
	{
	public:

		CPCharSelected(SGameServerInterfaces* interfaces, irr::u32 char_id)
		: CServerPacket(), Interfaces(interfaces), CharId(char_id)
		{
			Priority = EPP_URGENT;
		};

		virtual ~CPCharSelected()
		{

		};

		virtual bool writePacket()
		{
			SCharInfo* ci = Interfaces->PlayerCache->loadChar(CharId);
			if(ci == 0)
				return false;
			SClassTemplate* ct = Interfaces->CharTemplates->loadTemplate(ci->ClassId);

			w8(0x15);

			wStrW(ci->Name); // Name
			w32(ci->CharacterId); // Char object id
			wStrW(ci->Title); // Title
			w32(0x00); // session id (why do we send this so many times?)
			w32(0x00); // Clan id
			w32(0x00);
			w32(ci->Sex); // Sex
			w32(ci->RaceId); // Race
			w32(ci->ClassId); // Class
			w32(0x01);

			w32(ci->x); // x
			w32(ci->y); // y
			w32(ci->z); // z

			wf(ci->hp); // Current hp
			wf(ci->mp); // Current mp
			w32(0x00); // Current sp
			w64(ci->xp); // Current xp
			w32(ci->Level); // Current lvl
			w32(0x00); // Current karma
			w32(0x00);
			w32(ct->INT); // INT
			w32(ct->STR); // STR
			w32(ct->CON); // CON
			w32(ct->MEN); // MEN
			w32(ct->DEX); // DEX
			w32(ct->WIT); // WIT

			for(irr::u32 i = 0; i < 30; i++)
			{
				w32(0x00);
			}

            w32(0x00);
            w32(0x00);
			w32(0x00);
            w32(0x00);
            w32(0x00);
            w32(0x7501); // Time
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

	private:

		SGameServerInterfaces* Interfaces;
		irr::u32 CharId;

	};

}
}

#endif
