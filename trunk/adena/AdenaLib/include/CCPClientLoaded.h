/*
 * CCPClientLoaded.h - Client loaded level.
 * Created January 24, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_C_P_CLIENT_LOADED_H_
#define _ADENA_C_C_P_CLIENT_LOADED_H_

#include <GameManager.h>
#include <CClientPacket.h>

namespace adena
{
namespace game_server
{

	class CCPClientLoaded : public CClientPacket
	{
	public:

		CCPClientLoaded(irr::c8* in_data, IGameServerClient* client)
		: CClientPacket()
		{
			Client = client;
			Data = in_data;
			ReadPointer++;

			GameManager* gm = dynamic_cast<GameManager*>(Client->Server->Interfaces.GameManager);
			if(gm)
			{
				gm->playerEnterWorld(Client->CharInfo, Client);
			}
		};

		virtual ~CCPClientLoaded()
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
	};

}
}

#endif
