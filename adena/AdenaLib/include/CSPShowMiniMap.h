/*
 * CSPShowMiniMap.h - Tells client to show the map.
 * Created January 30, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_SHOW_MINI_MAP_H_
#define _ADENA_C_S_P_SHOW_MINI_MAP_H_

#include <CServerPacket.h>
#include <vector3d.h>

namespace adena
{
namespace game_server
{

	class CSPShowMiniMap : public CServerPacket
	{
	public:

		CSPShowMiniMap()
		: CServerPacket()
		{
			Priority = EPP_LOW;
		};

		virtual ~CSPShowMiniMap() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				w8(0x9d);
				w32(1665);

				Writen = true;
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
