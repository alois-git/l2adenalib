/*
 * CPCharSelect.h - Send key to client.
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

#ifndef _ADENA_C_P_CHAR_SELECT_H_
#define _ADENA_C_P_CHAR_SELECT_H_

#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CPCharSelect : public CServerPacket
	{
	public:

		CPCharSelect(IGameServerClient* client)
		: CServerPacket()
		{
			Priority = EPP_NORMAL;
			Client = client;
		};

		virtual ~CPCharSelect()
		{

		};

		virtual bool writePacket()
		{
			Client->CharSelectIds = Client->Server->Interfaces.PlayerCache->loadCharSelect(Client->AccountId);

			// Would much rather allocate memory once :P
			resize(Client->CharSelectIds.Chars * 256);

			w8(0x13);
			w32(Client->CharSelectIds.Chars);

			for (int i = 0; i < Client->CharSelectIds.Chars; i++)
			{
				SCharInfo* ci = Client->Server->Interfaces.PlayerCache->loadChar(Client->CharSelectIds.CharIds[i]);
				SClassTemplate* ct = Client->Server->Interfaces.CharTemplates->loadTemplate(ci->ClassId);

				wStrW(ci->Name); // Char name
				w32(ci->CharacterId); // Char id
				wStrW(irr::core::stringc("1337")); // Account name

				w32(0x00);
				w32(0x00);
				w32(0x00);

				w32(ci->Sex); // sex
				w32(ci->RaceId); // race id
				w32(ci->ClassId); // class id

				w32(0x01);

				w32(ci->x); // x
				w32(ci->y); // y
				w32(ci->z); // z

				wf(ci->hp); // Current hp
				wf(ci->mp); // Current mp
				w32(0x00); // Current sp
				w64(ci->xp); // Current xp
				w32(ci->Level);  // Current level

				w32(0x00); // Current karma
				w32(0x00);
				w32(0x00);
				w32(0x00);
				w32(0x00);
				w32(0x00);
				w32(0x00);
				w32(0x00);
				w32(0x00);
				w32(0x00);

				// Object ids
				w32(0x00); // Underware
				w32(0x00); // Rear
				w32(0x00); // Left rear
				w32(0x00); // Neckless
				w32(0x00); // Right ring
				w32(0x00); // Left ring
				w32(0x00); // Helmate
				w32(0x00); // Right hand
				w32(0x00); // Left hand
				w32(0x00); // Gloves
				w32(0x00); // Main armor
				w32(0x00); // Leggings
				w32(0x00); // Boots
				w32(0x00); // Back
				w32(0x00); // Left right hand
				w32(0x00); // Hair

				// Item ids
				w32(0x00); // Underware
				w32(0x00); // Rear
				w32(0x00); // Left rear
				w32(0x00); // Neckless
				w32(0x00); // Right ring
				w32(0x00); // Left ring
				w32(0x00); // Helmate
				w32(0x00); // Right hand
				w32(0x00); // Left hand
				w32(0x00); // Gloves
				w32(0x00); // Main armor
				w32(0x00); // Leggings
				w32(0x00); // Boots
				w32(0x00); // Back
				w32(0x00); // Left right hand
				w32(0x00); // Hair

				w32(ci->HairType); // Hair type
				w32(ci->HairColor); // Hair color
				w32(ci->FaceType); // Face type

				wf(1337); // Max hp
				wf(1337); // Max mp

				w32(0x00); // Days before delete

				w32(ci->ClassId); // Class id

				w32(0x00); // Bool, last used

				w8(0x00); // Enchant level
				w32(0x00); // Object id mask
				w32(0x00); // Item id mask
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

	private:

	};

}
}

#endif
