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
#include <CPProtocolVersion.h>

#define RECV_SIZE 65536 // Max size of a L2 packet.

static const irr::c8 key[8] = {0x94, 0x35, 0x00, 0x00, 0xa1, 0x6c,	0x54, 0x87};

namespace adena
{

CGameServerClient::CGameServerClient(irr::net::IServerClient* client, CGameServer* server)
: Client(client), Server(server), SessionId(0), CryptPackets(false)
{
	for(int i = 0; i < 256; i++)
		PacketFunctions[i] = &CGameServerClient::unknownPacket;
	PacketFunctions[0] = &CGameServerClient::protocolVersion;
};

CGameServerClient::~CGameServerClient()
{

};

void CGameServerClient::HandlePacket()
{
	irr::c8 buff[RECV_SIZE];
	Client->recv(buff, 2);
	int size = 0;
	size += (unsigned char)buff[0];
	size += ((unsigned char)(buff[1]) * 256);
	int recv_len = Client->recv(buff, size - 2);
	if(recv_len != (size - 2))
	{
		// Invalid packet.
		Server->Server->kickClient(Client);
	}
	if(CryptPackets)
	{
		InputCipher->decrypt(buff, size - 2);
	}
	(this->*PacketFunctions[buff[0]])(buff);
};

void CGameServerClient::SendPacket(IPacket* packet)
{

};

//========================================

void CGameServerClient::unknownPacket(irr::c8* data)
{
	printf("Recived unknown packet of type %d\n", data[0]);
};

void CGameServerClient::protocolVersion(irr::c8* data)
{
	CPProtocolVersion pv(data);
	printf("User connected with proto version %d\n", pv.ProtocolVersion);
};

}
