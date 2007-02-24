/*
 * CGameServer.h - Game server.
 * Created January 6, 2006, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_GAME_SERVER_H_
#define _ADENA_C_GAME_SERVER_H_

#include <AdenaConfig.h>
#include <irrThread.h>
#include <irrNet.h>
#include <irrList.h>
#include <CLogger.h>
#include <SGameServerInterfaces.h>
#include <SClassTemplate.h>
#include <ILoginServerLink.h>
#include <AVL.h>

namespace adena
{
namespace game_server
{

	class ADENALIB_API CGameServer : public irr::core::threads::Thread, public irr::net::INetEvent
	{
	public:

		/*
		 * @param addr: The address to bind to.
		 * result: Server is initalized and bound to addr.
		 */
		CGameServer();

		virtual ~CGameServer();

		static COObject* getGMInstance(IOObjectSystem* objsys = 0, irr::core::stringc name = "Engine.GameManager");

		virtual void OnEvent(irr::net::NetEvent &e);

		virtual bool init(const char* config_file);

		virtual void loginLinkEvent(SLoginLinkEvent e);

		virtual void run();

		SGameServerInterfaces Interfaces;
		irr::net::IServer* Server;
		irr::core::threads::Mutex CreateCharMutex;
		ILoginServerLink* LoginServerLink;

		irr::u32 CurrentPlayerCount;

		struct SAccountUser
		{
			irr::u32 AccountId;
			irr::u32 SessionId;
			irr::c8 LoginState; // 0 = waiting to log in, 1 = logged in, 2 = kick request before use could log in.
		};

		// Maps account names to account/session ids
		AVL<irr::core::stringc, SAccountUser> WaitingToLogin;
		irr::core::threads::Mutex WaitingToLoginMutex;

		// Maps account ids to user info
		AVL<irr::u32, SAccountUser> AccountUsers;
		irr::core::threads::Mutex AccountUsersMutex;

		// Maps account names to char ids
		AVL<irr::core::stringc, irr::u32> Accounts;
		irr::core::threads::Mutex AccountsMutex;
		
	};

}
}

#endif
