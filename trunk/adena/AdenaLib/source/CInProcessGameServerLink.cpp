/*
 * CInProcessGameServerLink.cpp - Loginserver -> Gameserver communication when in the same memory space.
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

// For CInProcessLoginServerLink

bool CInProcessGameServerLink::regServer(irr::u32 server_id, void* login_server_link, irr::c8 ip[4], irr::u16 port)
{
	SGameLinkEvent gle;
	gle.ServerId = server_id;
	gle.EventType = EGLET_REGISTER_REQUEST;
	memcpy(gle.RegisterRequest.Ip, ip, 4);
	gle.RegisterRequest.Port = port;

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
