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
#include <CPKeyInit.h>
#include <CPAuthLogin.h>
#include <CPCharSelect.h>
#include <CPCharTemplate.h>
#include <CPCharCreate.h>

#define RECV_SIZE 65536 // Max size of a L2 packet.

static const irr::c8 key[8] = {0x94, 0x35, 0x00, 0x00, 0xa1, 0x6c,	0x54, 0x87};

namespace adena
{
namespace game_server
{

CGameServerClient::CGameServerClient(irr::net::IServerClient* client, CGameServer* server)
: Client(client), Server(server), SessionId(0), CryptPackets(false)
{
	OutputCipher = new CCrypt((irr::c8*)key);
	InputCipher = new CCrypt((irr::c8*)key);
	// Set all packets to default to unknown (don't want to try to call a function thats not there :P)
	for(int i = 0; i < 256; i++)
		PacketFunctions[i] = &CGameServerClient::unknownPacket;

	PacketFunctions[0] = &CGameServerClient::protocolVersion;
	PacketFunctions[8] = &CGameServerClient::authLogin;
	PacketFunctions[9] = &CGameServerClient::logout;
	PacketFunctions[11] = &CGameServerClient::createChar;
	PacketFunctions[14] = &CGameServerClient::createCharButtion;
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

	(this->*PacketFunctions[buff[0] & 0xff])(buff);
};

void CGameServerClient::sendPacket(IPacket* packet)
{
	irr::c8 buff[RECV_SIZE];
	irr::c8* data = packet->getData();
	irr::u32 len = packet->getLen();
	if(CryptPackets)
		OutputCipher->encrypt(data, len);
	buff[0] = ((len + 2) & 0xff);
	buff[1] = (((len + 2) >> 8) & 0xff);
	memcpy(buff + 2, data, len);
	Client->send(buff, len + 2);
};

//========================================

void CGameServerClient::unknownPacket(irr::c8* data)
{
	printf("Recived unknown packet of type %d\n", data[0]);
};

// 0
void CGameServerClient::protocolVersion(irr::c8* data)
{
	CPProtocolVersion pv(data);
	printf("User connected with proto version %d\n", pv.ProtocolVersion);
	CPKeyInit ki((irr::c8*)key);
	sendPacket(&ki);
	CryptPackets = true;
};

// 8
void CGameServerClient::authLogin(irr::c8* data)
{
	CPAuthLogin al(data);
	printf("Account name %s\n", al.AccountName.c_str());
	printf("Auth login: %d, %d, %d, %d\n", al.Id1, al.Id2, al.Id3, al.Id4);
	CPCharSelect cs = CPCharSelect();
	sendPacket(&cs);
};

// 9
void CGameServerClient::logout(irr::c8* data)
{
	// Packet has no content.
};

// 11
void CGameServerClient::createChar(irr::c8* data)
{
	CPCharCreate cc(data);
	printf("Create char %s\n", cc.Name.c_str());
};

// 14
void CGameServerClient::createCharButtion(irr::c8* data)
{
	CPCharTemplate ct(Server->ClassTemplateList);
	sendPacket(&ct);
};

}
}
