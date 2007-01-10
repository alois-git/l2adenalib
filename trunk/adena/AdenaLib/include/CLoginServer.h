/*
 * CLoginServer.h - Login server.
 * Created December 31, 2006, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_LOGIN_SERVER_H_
#define _ADENA_C_LOGIN_SERVER_H_

#include <AdenaConfig.h>
#include <irrThread.h>
#include <irrNet.h>
#include <SLoginServerInterfaces.h>
#include <irrList.h>
#include <CLoginServerNetEvent.h>
#include <CPServerList.h>
#include <SLoginServerStatus.h>
#include <time.h>
#include <IGameServerLink.h>
#include <AVL.h>

namespace adena
{
namespace login_server
{

	class ADENALIB_API CLoginServer : public irr::core::threads::Thread
	{
	public:

		struct SAccountLocation
		{
			bool Local; // true: Data is a pointer to an IServerClient. false: Data is a pointer to an IGameServerLink
			void* Data;
		};

		/*
		 *
		 */
		CLoginServer();

		virtual ~CLoginServer();

		/*
		 * @param config_file: [IN] Null terminated string of the configuration file name
		 * return: true on sucess, false on error. You should not call start() if this returns false
		 */
		virtual bool init(const char* config_file);

		/*
		 * Internal use only
		 */
		virtual void gameLinkEvent(SGameLinkEvent e);

		/*
		 * Internal use only
		 */
		virtual void run();

		/*
		 * return: The currernt login server status
		 */
		virtual SLoginServerStatus getStatus();

		/*
		 * Internal use only
		 */
		virtual bool loginAccount(irr::u32 account_id, irr::net::IServerClient* client);

		/*
		 * Internal use only
		 */
		virtual void unlogAccount(irr::u32 account_id);


		SLoginServerInterfaces Interfaces;

		char ScrambledMod[128];
		irr::net::IServer* Server;

		// Server list sent to clients on the same network (LAN)
		CPServerList* InternalServerListPacket;

		// Server list sent to clients on teh internets (WAN)
		CPServerList* ExternalServerListPacket;

		SLoginServerStatus ServerStatus;
		IGameServerLink* GameServerLink;

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
