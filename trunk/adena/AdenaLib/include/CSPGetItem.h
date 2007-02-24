/*
 * CSPGetItem.h - Player picked up anditem.
 * Created February 21, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_GET_ITEM_H_
#define _ADENA_C_S_P_GET_ITEM_H_

#include <Actor.h>
#include <CServerPacket.h>
#include <irrList.h>
#include <ItemOnGround.h>

namespace adena
{
namespace game_server
{

	class CSPGetItem : public CServerPacket
	{
	public:

		CSPGetItem(ItemOnGround* item, irr::u32 getter_id)
		: CServerPacket(), Item(item), Id(getter_id)
		{
			Priority = EPP_LOW;
		};

		virtual ~CSPGetItem() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x0d);

				w32(Id);
				w32(Item->Id);
				w32(Item->Location.X);
				w32(Item->Location.Y);
				w32(Item->Location.Z);
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

		ItemOnGround* Item;
		irr::u32 Id;

	};

}
}

#endif
