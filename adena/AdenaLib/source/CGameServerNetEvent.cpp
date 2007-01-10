/*
 * CGameServerNetEvent.cpp - Login server network events.
 * Created January 6, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CGameServerNetEvent.h>
#include <CGameServerClient.h>

namespace adena
{
namespace game_server
{

NEGameServerNetEvent::NEGameServerNetEvent(void* server)
: Server(server)
{

};

NEGameServerNetEvent::~NEGameServerNetEvent()
{

};

void NEGameServerNetEvent::OnEvent(irr::net::NetEvent &e)
{
	switch(e.enet)
	{
		case irr::net::ENET_CLIENT_CONNECT:
			e.serverClient->UserData = new CGameServerClient(e.serverClient, (CGameServer*)Server);
			break;
		case irr::net::ENET_CLIENT_DISCONNECT:
			delete ((CGameServerClient*)e.serverClient->UserData);
			break;
		case ::irr::net::ENET_RECVDATA:
			((CGameServerClient*)e.serverClient->UserData)->HandlePacket();
			break;
	}
};

}
}
