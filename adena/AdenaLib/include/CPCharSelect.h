/*
 * CPCharSelect.h - Send key to client.
 * Created January 7, 2007, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Michael Spencer - bigcheesegs@gmail.com
 */

#ifndef _ADENA_C_P_CHAR_SELECT_H_
#define _ADENA_C_P_CHAR_SELECT_H_

#include <CPacket.h>

namespace adena
{
namespace game_server
{

	class CPCharSelect : public CPacket
	{
	public:

		CPCharSelect(irr::db::IDatabase* db, irr::core::stringc& acc)
		: CPacket()
		{
			irr::db::Query chars(irr::core::stringc("SELECT * FROM characters WHERE account_name = '$acc'"));
			chars.setVar(irr::core::stringc("$acc"), acc);
			irr::db::CQueryResult qr = db->query(chars);

			irr::u32 len = qr.RowCount;

			w8(0x13);
			w32(len);

			for (int i = 0; i < len; i++)
			{
				wStrW(qr[i][irr::core::stringc("name")]); // Char name
				w32(atoi(qr[i][irr::core::stringc("id")].c_str())); // Char id, no reason
				wStrW(acc); // Account name, no reason.

				w32(0x00);
				w32(0x00);
				w32(0x00);

				w32(atoi(qr[i][irr::core::stringc("sex")].c_str())); // sex
				w32(atoi(qr[i][irr::core::stringc("race_id")].c_str())); // race id
				w32(atoi(qr[i][irr::core::stringc("class_id")].c_str())); // class id

				w32(0x01);

				w32(0x00); // x
				w32(0x00); // y
				w32(0x00); // z

				wf(0x00); // Current hp
				wf(0x00); // Current mp
				w32(0x00); // Current sp
				w64(0x00); // Current xp
				w32(80);  // Current level

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

				w32(atoi(qr[i][irr::core::stringc("hair_type")].c_str())); // Hair type
				w32(atoi(qr[i][irr::core::stringc("hair_color")].c_str())); // Hair color
				w32(atoi(qr[i][irr::core::stringc("face")].c_str())); // Face type

				wf(100); // Max hp
				wf(100); // Max mp

				w32(0x00); // Days before delete

				w32(atoi(qr[i][irr::core::stringc("class_id")].c_str())); // Class id

				w32(0x00); // Bool, last used

				w8(0x00); // Enchant level
				w32(0x00); // Object id mask
				w32(0x00); // Item id mask
			}
		};

		virtual ~CPCharSelect()
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
