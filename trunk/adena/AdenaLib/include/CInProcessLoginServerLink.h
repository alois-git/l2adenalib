/*
 * CInProcessLoginServerLink.h - Gameserver -> Loginserver communication when in the same memory space.
 * Created January 8, 2007, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Michael Spencer - bigcheesegs@gmail.com
 */

#ifndef _ADENA_C_IN_PROCESS_LOGIN_SERVER_LINK_H_
#define _ADENA_C_IN_PROCESS_LOGIN_SERVER_LINK_H_

#include <ILoginServerLink.h>

namespace adena
{
namespace game_server
{

	/*
	 * This class allows us to hide the interface used between the login server and game server.
	 * All calls are async, so when you call registerWithLoginServer, the LoginServerLink will call
	 * registerWithLoginServerResult(bool) on the game server.
	 */

	class ADENALIB_API CInProcessLoginServerLink : public ILoginServerLink
	{
	public:

		CInProcessLoginServerLink(void* gameserver, void* gameserverlink, irr::u32 server_id);

		virtual ~CInProcessLoginServerLink();

		virtual void registerWithLoginServer(irr::c8 ip[4], irr::u16 port);

		void* GameServerLink;
		void* GameServer;

		// For CInProcessGameServerLink

		void kickAccount(irr::u32 account_id);

	private:

		irr::u32 ServerId;

	};

}
}

#endif
