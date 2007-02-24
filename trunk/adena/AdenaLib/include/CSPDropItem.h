/*
 * CSPDropItem.h - Item dropped.
 * Created February 20, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_DROP_ITEM_H_
#define _ADENA_C_S_P_DROP_ITEM_H_


#include <CServerPacket.h>
#include <ItemOnGround.h>

namespace adena
{
namespace game_server
{

	class CSPDropItem : public CServerPacket
	{
	public:

		CSPDropItem(Actor* dropper, ItemOnGround* item)
		: CServerPacket(), Dropper(dropper), Item(item)
		{
			Priority = EPP_NORMAL;
		};

		virtual ~CSPDropItem() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x0c);
				
				w32(Dropper->Id);
				w32(Item->Id);
				w32(Item->ItemInfo->ItemId);
				w32(Item->Location.X);
				w32(Item->Location.Y);
				w32(Item->Location.Z);
				((Item->ItemInfo->ETCItem.ConsumeType == ECT_Stackable) || (Item->ItemInfo->ETCItem.ConsumeType == ECT_Asset)) ? w32(1) : w32(0); // Stackable
				w32(Item->ItemCount); // Count
				w32(1); // ?
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

		Actor* Dropper;
		ItemOnGround* Item;

	};

}
}

#endif
