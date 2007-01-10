/*
 * CInProcessLoginServerLink.cpp - Gameserver -> Loginserver communication when in the same memory space.
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

#include <CInProcessLoginServerLink.h>
#include <CInProcessGameServerLink.h>
#include <CGameServer.h>

namespace adena
{
namespace game_server
{

CInProcessLoginServerLink::CInProcessLoginServerLink(void* gameserver, void* gameserverlink, irr::u32 server_id)
: GameServer(gameserver), GameServerLink(gameserverlink), ServerId(server_id)
{

};

CInProcessLoginServerLink::~CInProcessLoginServerLink()
{

};

void CInProcessLoginServerLink::registerWithLoginServer(irr::c8 ip[4], irr::u16 port)
{
	if(((login_server::CInProcessGameServerLink*)GameServerLink)->regServer(ServerId, this, ip, port))
	{
		SLoginLinkEvent lle;
		lle.EventType = ELLET_REGISTER_RESULT;
		lle.Result = ELLR_OK;
		((CGameServer*)GameServer)->loginLinkEvent(lle);
	}else
	{
		SLoginLinkEvent lle;
		lle.EventType = ELLET_REGISTER_RESULT;
		lle.Result = ELLR_AUTH_FAILED;
		((CGameServer*)GameServer)->loginLinkEvent(lle);
	}
};

void CInProcessLoginServerLink::kickAccount(irr::u32 account_id)
{
	printf("Login Server requested kick of account_id %d\n", account_id);
};

}
}
