/*
 * CInProcessGameServerLink.h - Loginserver -> Gameserver communication when in the same memory space.
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

#ifndef _ADENA_C_IN_PROCESS_GAME_SERVER_LINK_H_
#define _ADENA_C_IN_PROCESS_GAME_SERVER_LINK_H_

#include <IGameServerLink.h>
#include <irrArray.h>
#include <CMutex.h>

namespace adena
{
namespace login_server
{

	/*
	 * This class allows us to hide the interface used between the login server and game server.
	 * All calls are async, so when you call registerWithLoginServer, the LoginServerLink will call
	 * registerWithLoginServerResult(bool) on the game server.
	 */

	class ADENALIB_API CInProcessGameServerLink : public IGameServerLink
	{
	public:

		CInProcessGameServerLink(void* loginserver);

		virtual ~CInProcessGameServerLink();

		virtual void registerResult(irr::u32 server_id);

		virtual void requestKick(irr::u32 server_id, irr::u32 account_id);

		virtual void requestServerInfo(irr::u32 server_id);

		virtual void requestPlay(irr::u32 server_id, irr::core::stringc account_name, irr::u32 account_id, irr::u32 session_id);

		void* LoginServer;

		// For CInProcessLoginServerLink

		bool regServer(irr::u32 server_id, void* login_server_link);

	private:

		// Pointers to CInProcessLoginServerLinks
		irr::core::array<void*> LoginLinks;
		irr::core::threads::Mutex LoginLinksMutex;
		irr::u32 ServerId;

	};

}
}

#endif
