/*
 * CCPMoveToLocation.h - Move packet
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

#ifndef _ADENA_C_C_P_MOVE_TO_LOCATION_H_
#define _ADENA_C_C_P_SAY_H_

#include <CClientPacket.h>
#include <irrString.h>
#include <CSPMoveToLocation.h>
#include <vector3d.h>
#include <CSPStopMove.h>

namespace adena
{
namespace game_server
{

	class CCPMoveToLocation : public CClientPacket
	{
	public:

		CCPMoveToLocation(irr::c8* in_data, IGameServerClient* client)
		: CClientPacket()
		{
			Client = client;
			Data = in_data;
			ReadPointer++;

			Target.X = r32();
			Target.Y = r32();
			Target.Z = r32();
			Origin.X = r32();
			Origin.Y = r32();
			Origin.Z = r32();
			MoveType = r32();

			client->CharInfo->x = Target.X;
			client->CharInfo->y = Target.Y;
			client->CharInfo->z = Target.Z;

			start();
		};

		virtual ~CCPMoveToLocation()
		{
			Data = 0;
		};

		virtual void run()
		{
			//Client->s
			AVL<irr::u32, COPawn*>::Iterator<irr::u32, COPawn*> ittr(&Client->Server->Players);
			irr::u32 key;
			COPawn* item;
			if(ittr.GetFirst(key, item))
			{
				CSPMoveToLocation* mtl = new CSPMoveToLocation(Client->CharInfo->CharacterId, Target, Origin);
				mtl->getRef();
				while(true)
				{
					// Do stuff with item
					COPlayer* p = (COPlayer*)item;
					p->Client->sendPacket(mtl);
					if(!ittr.GetNext(key, item))
						break;
				}
				mtl->drop(); // So that non of the clients delete the packet before all of them get a change to getRef()
			}

			/*irr::core::threads::sleep(1000);

			if(ittr.GetFirst(key, item))
			{
				CSPStopMove* sm = new CSPStopMove(Client->CharInfo->CharacterId, Target, 0);
				while(true)
				{
					// Do stuff with item
					COPlayer* p = (COPlayer*)item;
					p->Client->sendPacket(sm);
					if(!ittr.GetNext(key, item))
						break;
				}
			}*/

			delete this;
		};

		virtual irr::c8* getData()
		{
			return NULL;
		};

		virtual irr::u32 getLen()
		{
			return 0;
		};

		irr::core::vector3di Target;
		irr::core::vector3di Origin;
		irr::u32 MoveType;
	};

}
}

#endif
