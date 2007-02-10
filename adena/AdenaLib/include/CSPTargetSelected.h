/*
 * CSPTargetSelected.h - Notifies client that they selected a target.
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

#ifndef _ADENA_C_S_P_TARGET_SELECTED_H_
#define _ADENA_C_S_P_TARGET_SELECTED_H_

#include <CServerPacket.h>
#include <vector3d.h>

namespace adena
{
namespace game_server
{

	class CSPTargetSelected : public CServerPacket
	{
	public:

		CSPTargetSelected(irr::u32 targeter_id, irr::u32 targetie_id, irr::core::vector3df target_loc)
		: CServerPacket(), TargeterId(targeter_id), TargeteiId(targetie_id), TargetLoc(target_loc)
		{
			Priority = EPP_HIGH;
		};

		virtual ~CSPTargetSelected() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x29);

				w32(TargeterId);
				w32(TargeteiId);
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
		irr::u32 TargeteiId;
		irr::core::vector3df TargetLoc;

	};

}
}

#endif
