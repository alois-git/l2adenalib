/*
 * CCPClickObj.h - Client clicked on something targetable.
 * Created January 26, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_C_P_CLICK_OBJ_H_
#define _ADENA_C_C_P_CLICK_OBJ_H_

#include <GameManager.h>
#include <CClientPacket.h>

namespace adena
{
namespace game_server
{

	class CCPClickObj : public CClientPacket
	{
	public:

		CCPClickObj(irr::c8* in_data, IGameServerClient* client)
		: CClientPacket()
		{
			Client = client;
			Data = in_data;
			ReadPointer++;

			Controller* c = dynamic_cast<Controller*>(Client->PController);
			if(c)
			{
				ObjId = r32();
				Origin.X = r32();
				Origin.Y = r32();
				Origin.Z = r32();
				ShiftClick = r8(); // true = shift, false = no shift.

				Actor* a = dynamic_cast<Actor*>(Client->Server->Interfaces.ObjectSystem->getObj(ObjId));
				if(a)
				{
					c->clickObject(a, ShiftClick);
				}else
				{
					Client->Server->Interfaces.Logger->log("Client tried to click on an object that is not in the world.", irr::ELL_WARNING);
				}
			}
		};

		virtual ~CCPClickObj()
		{
			Data = 0;
		};

		virtual void run()
		{

		};

		virtual irr::c8* getData()
		{
			return NULL;
		};

		virtual irr::u32 getLen()
		{
			return 0;
		};

		irr::u32 ObjId;
		irr::core::vector3df Origin;
		bool ShiftClick;

	};

}
}

#endif
