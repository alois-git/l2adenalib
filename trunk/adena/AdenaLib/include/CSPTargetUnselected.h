/*
 * CSPTargetUnselected.h - Notifies client that they unselected a target.
 * Created February 8, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_TARGET_UNSELECTED_H_
#define _ADENA_C_S_P_TARGET_UNSELECTED_H_

#include <CServerPacket.h>
#include <vector3d.h>

namespace adena
{
namespace game_server
{

	class CSPTargetUnselected : public CServerPacket
	{
	public:

		CSPTargetUnselected(irr::u32 targeter_id, irr::core::vector3df target_loc)
		: CServerPacket(), TargeterId(targeter_id), TargetLoc(target_loc)
		{
			Priority = EPP_HIGH;
		};

		virtual ~CSPTargetUnselected() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x2a);

				w32(TargeterId);
				w32(TargetLoc.X);
				w32(TargetLoc.Y);
				w32(TargetLoc.Z);
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

		irr::u32 TargeterId;
		irr::core::vector3df TargetLoc;

	};

}
}

#endif
