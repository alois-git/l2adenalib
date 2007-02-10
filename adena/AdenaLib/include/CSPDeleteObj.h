/*
 * CSPDeleteObj.h - Notifies client that an obj got pwned.
 * Created January 27, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_DELETE_OBJ_H_
#define _ADENA_C_S_P_DELETE_OBJ_H_

#include <CServerPacket.h>
#include <vector3d.h>

namespace adena
{
namespace game_server
{

	class CSPDeleteObj : public CServerPacket
	{
	public:

		CSPDeleteObj(irr::u32 obj_id)
		: CServerPacket(), ObjId(obj_id)
		{
			Priority = EPP_LOW;
		};

		virtual ~CSPDeleteObj() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x12);

				w32(ObjId);
				w32(0x00);
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

		irr::u32 ObjId;

	};

}
}

#endif
