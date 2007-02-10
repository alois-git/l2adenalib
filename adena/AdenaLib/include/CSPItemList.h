/*
 * CSPItemList.h - Send the client their item list.
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

#ifndef _ADENA_C_S_P_ITEM_LIST_H_
#define _ADENA_C_S_P_ITEM_LIST_H_

#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CSPItemList : public CServerPacket
	{
	public:

		CSPItemList(bool show_window)
		: CServerPacket(), ShowWindow(show_window)
		{
			if (ShowWindow)
			{
				Priority = EPP_NORMAL;
			}else
			{
				Priority = EPP_NOT_REQUIRED;
			}
		};

		virtual ~CSPItemList() {};

		virtual bool writePacket()
		{
			w8(0x1b);
			if (ShowWindow)
			{
				w16(0x01);
			}else
			{
				w16(0x00);
			}

			w16(0x01); // Items

			//for(;;)
			{				
				w16(0x00); // Item type1
				w32(0x01); // Object id
				w32(57); // Item id ADENA PLIX!
				w32(2147483647); // Count (That's alot of adena!).
				w16(0x00);	// Item type2
				w16(0x00);	// Item type3
				w16(0x00); // Equipted?
				w32(0x00);	// Body part rev 415  slot 0006-lr.ear  0008-neck  0030-lr.finger  0040-head  0080-??  0100-l.hand  0200-gloves  0400-chest  0800-pants  1000-feet  2000-??  4000-r.hand  8000-r.hand
				w16(0x00);	// Enchant level
				w16(0x00);	// Item type3
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

		bool ShowWindow;

	};

}
}

#endif
