/*
 * CSPStopMove.h - Notifies that a obj stoped moving.
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

#ifndef _ADENA_C_S_P_STOP_MOVE_H_
#define _ADENA_C_S_P_STOP_MOVE_H_

#include <CServerPacket.h>
#include <vector3d.h>

namespace adena
{
namespace game_server
{

	class CSPStopMove : public CServerPacket
	{
	public:

		CSPStopMove(irr::u32 char_id, irr::core::vector3df loc, irr::s32 heading)
		: CServerPacket(), CharId(char_id), Loc(loc), Heading(heading)
		{
			Priority = EPP_URGENT;
		};

		virtual ~CSPStopMove() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x47);

				w32(CharId);
				w32(Loc.X);
				w32(Loc.Y);
				w32(Loc.Z);
				w32(Heading);				
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

		irr::u32 CharId;
		irr::core::vector3df Loc;
		irr::s32 Heading;

	};

}
}

#endif
