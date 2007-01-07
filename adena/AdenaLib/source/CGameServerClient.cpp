/*
 * CGameServerClient.cpp - Login server client.
 * Created January 7, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CGameServerClient.h>

#define RECV_SIZE 65536 // Max size of a L2 packet.

namespace adena
{

CGameServerClient::CGameServerClient(irr::net::IServerClient* client, CGameServer* server)
: Client(client), Server(server), SessionId(0)
{
	puts("Gameserver someone connected?!");
};

CGameServerClient::~CGameServerClient()
{

};

void CGameServerClient::HandlePacket()
{
	irr::c8 buff[RECV_SIZE];
	Client->recv(buff, 2);
};

void CGameServerClient::SendPacket(IPacket* packet)
{

};

}
