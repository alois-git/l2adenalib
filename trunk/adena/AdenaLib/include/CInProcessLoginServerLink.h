/*
 * CInProcessLoginServerLink.h - Gameserver -> Loginserver communication when in the same memory space.
 * Created January 8, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_IN_PROCESS_LOGIN_SERVER_LINK_H_
#define _ADENA_C_IN_PROCESS_LOGIN_SERVER_LINK_H_

#include <ILoginServerLink.h>
#include <SGameServerInfo.h>

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

		virtual void registerWithLoginServer();

		void* GameServerLink;
		void* GameServer;

		// For CInProcessGameServerLink

		void kickAccount(irr::u32 account_id);

		SGameServerInfo getServerInfo();

		void requestPlay(irr::core::stringc account_name, irr::u32 account_id, irr::u32 session_id);

	private:

		irr::u32 ServerId;

	};

}
}

#endif
