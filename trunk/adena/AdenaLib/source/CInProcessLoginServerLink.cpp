/*
 * CInProcessLoginServerLink.cpp - Gameserver -> Loginserver communication when in the same memory space.
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

void CInProcessLoginServerLink::registerWithLoginServer()
{
	if(((login_server::CInProcessGameServerLink*)GameServerLink)->regServer(ServerId, this))
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

SGameServerInfo CInProcessLoginServerLink::getServerInfo()
{
	SGameServerInfo ret;
	SLoginLinkEvent lle;
	lle.EventType = ELLET_REQUEST_SERVER_INFO;
	lle.Result = ELLR_OK;
	lle.RequestServerInfo.ServerInfo = &ret;
	((CGameServer*)GameServer)->loginLinkEvent(lle);
	return ret;
};

void CInProcessLoginServerLink::requestPlay(irr::core::stringc account_name, irr::u32 account_id, irr::u32 session_id)
{
	SLoginLinkEvent lle;
	lle.EventType = ELLET_PLAY_REQUEST;
	lle.Result = ELLR_OK;
	lle.PlayRequest.AccountName = account_name;
	lle.PlayRequest.AccountId = account_id;
	lle.PlayRequest.SessionId = session_id;
	((CGameServer*)GameServer)->loginLinkEvent(lle);
};

}
}
