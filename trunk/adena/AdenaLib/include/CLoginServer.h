/*
 * CLoginServer.h - Login server.
 * Created December 31, 2006, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_LOGIN_SERVER_H_
#define _ADENA_C_LOGIN_SERVER_H_

#include <AdenaConfig.h>
#include <irrThread.h>
#include <irrNet.h>
#include <irrDb.h>
#include <irrRng.h>
#include <irrList.h>
#include <BDRSA.h>
#include <CLoginServerNetEvent.h>
#include <CBlowfish.h>
#include <CPServerList.h>
#include <SLoginServerStatus.h>
#include <time.h>
#include <IGameServerLink.h>
#include <AVL.h>
#include <ILogger.h>

namespace adena
{
namespace login_server
{

	class ADENALIB_API CLoginServer : public irr::core::threads::Thread
	{
	public:

		struct SAccountLocation
		{
			bool Local; // true: Data is a pointer to an IServerClient. false: Data is a pointer to an IGameServerLink.
			void* Data;
		};

		/*
		 * @param addr: The address to bind to.
		 * result: Server is initalized and bound to addr.
		 * A RSA key is generated, scrambled and stored.
		 */
		CLoginServer(irr::net::Address &addr);

		virtual ~CLoginServer();

		virtual void gameLinkEvent(SGameLinkEvent e);

		virtual void run();

		virtual SLoginServerStatus getStatus();

		// returns false if account already logged in (kicks client), true if account added to account list.
		virtual bool loginAccount(irr::u32 account_id, irr::net::IServerClient* client);

		// Called when a client disconnects or the game server tells us a client disconnected.
		virtual void unlogAccount(irr::u32 account_id);

		char ScrambledMod[128];
		BDRSA* RsaCipher;
		CBlowfish* BlowfishCipher;
		irr::net::IServer* Server;
		irr::db::IDatabase* DataBase;
		irr::IRng* Rng;
		CPServerList* ServerListPacket;
		SLoginServerStatus ServerStatus;
		IGameServerLink* GameServerLink;
		irr::ILogger* Logger;

		AVL<irr::u32, SAccountLocation> AccountLocations;
		irr::core::threads::Mutex AccountLocationsMutex;

	private:

		void ScrambleRsaPublicMod();
		NELoginServerNetEvent* EventParser;
		time_t StartTime;
		
	};

}
}

#endif
