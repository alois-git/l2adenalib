/*
 * CLoginServerNetEvent.cpp - Login server network events.
 * Created January 2, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CLoginServerNetEvent.h>
#include <CLoginServerClient.h>
#include <CLoginServer.h>

namespace adena
{
namespace login_server
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
			((CLoginServer*)Server)->ServerStatus.Connections++;
			break;
		case irr::net::ENET_CLIENT_DISCONNECT:
			if(((CLoginServerClient*)e.serverClient->UserData)->AccountId != 0)
				((CLoginServer*)Server)->unlogAccount(((CLoginServerClient*)e.serverClient->UserData)->AccountId);
			delete ((CLoginServerClient*)e.serverClient->UserData);
			break;
		case ::irr::net::ENET_RECVDATA:
			((CLoginServerClient*)e.serverClient->UserData)->HandlePacket();
			break;
	}
};

}
}
