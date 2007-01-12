/*
 * CGameServerClient.cpp - Login server client.
 * Created January 7, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CGameServerClient.h>
#include <CPProtocolVersion.h>
#include <CPKeyInit.h>
#include <CPAuthLogin.h>
#include <CPCharSelect.h>
#include <CPCharTemplate.h>
#include <CPCharCreate.h>
#include <CPCharCreateFailed.h>
#include <CPCharCreateOk.h>
#include <CPPressStart.h>
#include <CPCharInfo.h>
#include <CCPSay.h>
#include <CPUserInfo.h>
#include <CPLogout.h>
#include <SCharInfo.h>
#include <COPlayer.h>
#include <CCPMoveToLocation.h>
#include <CSPSystemMessage.h>

#define RECV_SIZE 65536 // Max size of a L2 packet.

static const irr::c8 key[8] = {0x94, 0x35, 0x00, 0x00, 0xa1, 0x6c,	0x54, 0x87};

namespace adena
{
namespace game_server
{

CGameServerClient::CGameServerClient(irr::net::IServerClient* client, CGameServer* server)
: CryptPackets(false)
{
	Pawn = 0;
	SessionId = 0;
	Server = server;
	Client = client;
	OutputCipher = new CCrypt((irr::c8*)key);
	InputCipher = new CCrypt((irr::c8*)key);
	// Set all packets with an unknown type to unknownPacket (don't want to try to call a function thats not there :P)
	for(int i = 0; i < 256; i++)
		PacketFunctions[i] = &CGameServerClient::unknownPacket;

	PacketFunctions[0] = &CGameServerClient::protocolVersion;
	PacketFunctions[1] = &CGameServerClient::moveToLocation;
	PacketFunctions[3] = &CGameServerClient::clientLoaded;
	PacketFunctions[8] = &CGameServerClient::authLogin;
	PacketFunctions[9] = &CGameServerClient::logout;
	PacketFunctions[11] = &CGameServerClient::createChar;
	PacketFunctions[13] = &CGameServerClient::pressStart;
	PacketFunctions[14] = &CGameServerClient::createCharButtion;
	PacketFunctions[56] = &CGameServerClient::clientSay;
	PacketFunctions[208] = &CGameServerClient::extendedPacket;
};

CGameServerClient::~CGameServerClient()
{
	if(Pawn != 0)
	{
		Server->PlayersMutex.getLock();
		Server->Players.Remove( ((COPlayer*)Pawn)->CharInfo->CharacterId );
		Server->PlayersMutex.releaseLock();
		delete Pawn;
	}
};

void CGameServerClient::HandlePacket()
{
	irr::c8 buff[RECV_SIZE];

	// Take the first 2 bytes to get the packet size
	Client->recv(buff, 2);
	int size = 0;
	size += (unsigned char)buff[0];
	size += ((unsigned char)(buff[1]) * 256);

	// Get the rest of the packet
	int recv_len = Client->recv(buff, size - 2);

	if(recv_len != (size - 2))
	{
		// Invalid packet.
		Server->Server->kickClient(Client);
	}

	if(CryptPackets)
	{
		// Decrypt the data using L2s usless xor cipher
		InputCipher->decrypt(buff, size - 2);
	}

	// Function pointers FTW
	(this->*PacketFunctions[buff[0] & 0xff])(buff);
};

void CGameServerClient::sendPacket(IPacket* packet)
{
	irr::c8 buff[RECV_SIZE];
	((CServerPacket*)packet)->writePacket();
	irr::c8* data = packet->getData();
	irr::u32 len = packet->getLen();
	buff[0] = ((len + 2) & 0xff);
	buff[1] = (((len + 2) >> 8) & 0xff);
	SendMutex.getLock();
	if(CryptPackets)
		OutputCipher->encrypt(data, len);
	memcpy(buff + 2, data, len);
	Client->send(buff, len + 2);
	SendMutex.releaseLock();
};

//========================================

void CGameServerClient::unknownPacket(irr::c8* data)
{
	printf("Recived unknown packet of type %d\n", (irr::u8)(data[0] & 0xff));
};

// 0
void CGameServerClient::protocolVersion(irr::c8* data)
{
	CPProtocolVersion pv(data);
	CPKeyInit ki((irr::c8*)key);
	sendPacket(&ki);
	CryptPackets = true;
};

// 1
void CGameServerClient::moveToLocation(irr::c8 *data)
{
	new CCPMoveToLocation(data, this);
};

// 3
void CGameServerClient::clientLoaded(irr::c8* data)
{
	// Client loaded, eat some adena.
	CPUserInfo ui = CPUserInfo(&Server->Interfaces, CharId);
	sendPacket(&ui);
	CPCharInfo ci = CPCharInfo(&Server->Interfaces, CharId);
	sendPacket(&ci);
	CSPSystemMessage sm("Welcome to L2Adena version ADENA_VERSION, have a nice day");
	sendPacket(&sm);
};

// 8
void CGameServerClient::authLogin(irr::c8* data)
{
	CPAuthLogin al(data);
	CGameServer::SAccountUser au;

	Server->WaitingToLoginMutex.getLock();
	if(Server->WaitingToLogin.Find(al.AccountName, au))
	{
		if(true)//au.SessionId == al.Id2) // TODO: Fix the stupid AVL tree
		{
			Server->WaitingToLogin.Remove(al.AccountName);
			if(Server->WaitingToLogin.Find(al.AccountName, au))
			{
				// Just removed it
				Server->Interfaces.Logger->log("Stupid server...");
			}
			AccountName = al.AccountName;
			AccountId = au.AccountId;
			CPCharSelect cs(this);
			sendPacket(&cs);
		}else
		{
			// An obvious hack attempt, or a code error :P
			Server->Interfaces.Logger->log("[HACK ALERT] User attempted to connect to game server with the correct account, but wrong session id");
		}
	}else
	{
		// An obvious hack attempt, or a code error :P
		Server->Interfaces.Logger->log("[HACK ALERT] User attempted to connect to game server with an account name not in the waiting list");
	}
	Server->WaitingToLoginMutex.releaseLock();

};

// 9
void CGameServerClient::logout(irr::c8* data)
{
	// Packet has no content.
	CPLogout l = CPLogout();
	sendPacket(&l);
};

// 11
void CGameServerClient::createChar(irr::c8* data)
{
	CPCharCreate cc(data);
	Server->CreateCharMutex.getLock();

	SCharInfo ci;
	ci.AccountId = AccountId;
	ci.Name = cc.Name;
	ci.Title = "";
	ci.RaceId = cc.Race;
	ci.ClassId = cc.ClassId; // TODO: Trusting the client to much
	ci.Sex = cc.Sex;
	ci.HairType = cc.HairStyle;
	ci.HairColor = cc.HairColor;
	ci.FaceType = cc.Face;

	if(Server->Interfaces.PlayerCache->createChar(ci))
	{
		// Char created
		CPCharCreateOk cco = CPCharCreateOk();
		sendPacket(&cco);
		CPCharSelect cs(this);
		sendPacket(&cs);
	}else
	{
		// Char creation failed
		CPCharCreateFailed ccf(CPCharCreateFailed::ECCFR_NAME_ALREADY_EXISTS);
		sendPacket(&ccf);
	}

	Server->CreateCharMutex.releaseLock();
};

// 13
void CGameServerClient::pressStart(irr::c8 *data)
{
	CPPressStart ps(data, this);
	CharId = CharSelectIds.CharIds[ps.CharIndex];
};

// 14
void CGameServerClient::createCharButtion(irr::c8* data)
{
	// Empty packet.
	CPCharTemplate ct = CPCharTemplate();
	sendPacket(&ct);
};

// 56
void CGameServerClient::clientSay(irr::c8* data)
{
	new CCPSay(data, this);
};

// 208
void CGameServerClient::extendedPacket(irr::c8* data)
{
	printf("Recived unknown extended packet of type %d\n", (irr::u8)(data[1] & 0xff));
}

}
}
