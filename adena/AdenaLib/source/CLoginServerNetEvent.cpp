/*
 * CLoginServerNetEvent.cpp - Login server network events.
 * Created January 2, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CLoginServerNetEvent.h>
#include <CLoginServerClient.h>

namespace adena
{

NELoginServerNetEvent::NELoginServerNetEvent(void* server)
: Server(server)
{

};

NELoginServerNetEvent::~NELoginServerNetEvent()
{

};

void NELoginServerNetEvent::OnEvent(irr::net::NetEvent &e)
{
	switch(e.enet)
	{
		case irr::net::ENET_CLIENT_CONNECT:
			e.serverClient->UserData = new CLoginServerClient(e.serverClient, (CLoginServer*)Server);
			printf("Client connected.\n");
			break;
		case irr::net::ENET_CLIENT_DISCONNECT:
			delete ((CLoginServerClient*)e.serverClient->UserData);
			printf("Client disconnected.\n");
			break;
		case ::irr::net::ENET_RECVDATA:
			printf("Client sent data.\n");
			((CLoginServerClient*)e.serverClient->UserData)->HandlePacket();
			break;
	}
};

}
