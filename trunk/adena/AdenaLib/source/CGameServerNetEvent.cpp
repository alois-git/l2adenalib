/*
 * CGameServerNetEvent.cpp - Login server network events.
 * Created January 6, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CGameServerNetEvent.h>
#include <CGameServerClient.h>

namespace adena
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
			printf("Game Client connected.\n");
			break;
		case irr::net::ENET_CLIENT_DISCONNECT:
			delete ((CGameServerClient*)e.serverClient->UserData);
			printf("Game Client disconnected.\n");
			break;
		case ::irr::net::ENET_RECVDATA:
			printf("Game Client sent data.\n");
			((CGameServerClient*)e.serverClient->UserData)->HandlePacket();
			break;
	}
};

}
