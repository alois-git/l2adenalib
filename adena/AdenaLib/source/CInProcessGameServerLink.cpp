/*
 * CInProcessGameServerLink.cpp - Loginserver -> Gameserver communication when in the same memory space.
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

#include <CInProcessGameServerLink.h>
#include <CInProcessLoginServerLink.h>
#include <CLoginServer.h>

namespace adena
{
namespace login_server
{

CInProcessGameServerLink::CInProcessGameServerLink(void* loginserver)
: LoginServer(loginserver)
{

};

CInProcessGameServerLink::~CInProcessGameServerLink()
{

};

void CInProcessGameServerLink::registerResult(irr::u32 server_id)
{
	
};

void CInProcessGameServerLink::requestKick(irr::u32 server_id, irr::u32 account_id)
{
	if(server_id >= LoginLinks.size())
	{
		// Invailid server_id
		return;
	}else
	{
		((game_server::CInProcessLoginServerLink*)LoginLinks[server_id])->kickAccount(account_id);
		SGameLinkEvent gle;
		gle.ServerId = server_id;
		gle.EventType = EGLET_CLIENT_DROPED;
		gle.ClientDroped.AccountId = account_id;
		((CLoginServer*)LoginServer)->gameLinkEvent(gle);
	}
};

void CInProcessGameServerLink::requestServerInfo(irr::u32 server_id)
{
	SGameServerInfo gsi = ((game_server::CInProcessLoginServerLink*)LoginLinks[server_id])->getServerInfo();
	SGameLinkEvent gle;
	gle.ServerId = gsi.ServerId;
	gle.EventType = EGLET_SERVER_INFO;
	gle.ServerInfo.GameServerInfo = gsi;
	((CLoginServer*)LoginServer)->gameLinkEvent(gle);
};

void CInProcessGameServerLink::requestPlay(irr::u32 server_id, irr::core::stringc account_name, irr::u32 account_id, irr::u32 session_id)
{
	((game_server::CInProcessLoginServerLink*)LoginLinks[server_id])->requestPlay(account_name, account_id, session_id);
}

// For CInProcessLoginServerLink

bool CInProcessGameServerLink::regServer(irr::u32 server_id, void* login_server_link)
{
	SGameLinkEvent gle;
	gle.ServerId = server_id;
	gle.EventType = EGLET_REGISTER_REQUEST;

	LoginLinksMutex.getLock();

	irr::u32 size = LoginLinks.size();

	// If server_id is not in the array, just make the array bigger and add it
	if(server_id >= size)
	{
		LoginLinks.reallocate(server_id + 1);
		LoginLinks.set_used(server_id + 1);

		// Set all the newly allocated pointers to 0
		for(irr::u32 i = size; i <= server_id; i++)
			LoginLinks[i] = 0;

		LoginLinks[server_id] = login_server_link;

		LoginLinksMutex.releaseLock();

		((CLoginServer*)LoginServer)->gameLinkEvent(gle);

		return true;
	}else // This server could already be registered
	{
		if(LoginLinks[server_id] != 0)
		{
			// Server already registered
			LoginLinksMutex.releaseLock();
			return false;
		}else
		{
			// Add the server
			LoginLinks[server_id] = login_server_link;

			LoginLinksMutex.releaseLock();

			((CLoginServer*)LoginServer)->gameLinkEvent(gle);

			return true;
		}
	}
};

}
}
