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
#include <CSPBuffBar.h>
#include <CSPMacroList.h>
#include <CSPItemList.h>
#include <CSPSkillBar.h>
#include <CSPDyes.h>
#include <CSPQuestList.h>

#define RECV_SIZE 65536 // Max size of a L2 packet.

static const irr::c8 key[8] = {0x94, 0x35, 0x00, 0x00, 0xa1, 0x6c,	0x54, 0x87};

namespace adena
{
namespace game_server
{

CGameServerClient::CGameServerClient(irr::net::IServerClient* client, CGameServer* server)
: ProtocolRevision(0)
{
	Pawn = 0;
	SessionId = 0;
	Server = server;
	Client = client;
	OutputCipher = new CCrypt((irr::c8*)key);
	InputCipher = new CCrypt((irr::c8*)key);
	PacketQueue = new CPacketQueue(20);

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
	PacketFunctions[15] = &CGameServerClient::requestItemList;
	PacketFunctions[56] = &CGameServerClient::clientSay;
	PacketFunctions[157] = &CGameServerClient::requestSkillCoolTime;
	PacketFunctions[208] = &CGameServerClient::extendedPacket;

	start();
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

void CGameServerClient::run()
{
	while(Running)
	{
		IPacket* packet = PacketQueue->getNextPacket();
		if(packet == NULL)
			irr::core::threads::sleep(0);
		else
		{
			if(((CServerPacket*)packet)->writePacket())
			{
				irr::c8 buff[RECV_SIZE];
				irr::c8* data = packet->getData();
				irr::u32 len = packet->getLen();
				buff[0] = ((len + 2) & 0xff);
				buff[1] = (((len + 2) >> 8) & 0xff);
				memcpy(buff + 2, data, len);
				if(packet->Crypt)
					OutputCipher->encrypt(buff + 2, len);
				Client->send(buff, len + 2);
			}
			packet->drop();
		}
	}
	delete PacketQueue;
	delete this;
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

	if(ProtocolRevision != 0)
	{
		// Decrypt the data using L2s usless xor cipher
		InputCipher->decrypt(buff, size - 2);
	}

	if((buff[0] & 0xff) != 0 && ProtocolRevision == 0)
		return; // Ya, bad dogy

	// Function pointers FTW
	(this->*PacketFunctions[buff[0] & 0xff])(buff);
};

void CGameServerClient::sendPacket(IPacket* packet)
{
	packet->getRef();
	PacketQueue->addPacket(packet);
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
	ProtocolRevision = pv.ProtocolVersion;
	sendPacket(new CPKeyInit((irr::c8*)key));
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
	IPacket* p;
	p = new CPUserInfo((COPlayer*)Pawn);
	sendPacket(p);
	p = new CPCharInfo((COPlayer*)Pawn);
	sendPacket(p);
	/*p = new CSPBuffBar();
	sendPacket(p);
	p = new CSPMacroList();
	sendPacket(p);
	p = new CSPItemList(false);
	sendPacket(p);
	p = new CSPSkillBar();
	sendPacket(p);
	p = new CSPDyes();
	sendPacket(p);
	p = new CSPQuestList();
	sendPacket(p);*/

	//irr::core::stringc msg("Welcome to L2Adena version $ver, have a nice day");
	//msg.replaceStr(irr::core::stringc("$ver"), irr::core::stringc(ADENA_VERSION));
	//sendPacket(new CSPSystemMessage(msg));
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
			sendPacket(new CPCharSelect(this));
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
	sendPacket(new CPLogout());
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
		sendPacket(new CPCharCreateOk());
		sendPacket(new CPCharSelect(this));
	}else
	{
		// Char creation failed
		sendPacket(new CPCharCreateFailed(CPCharCreateFailed::ECCFR_NAME_ALREADY_EXISTS));
	}

	Server->CreateCharMutex.releaseLock();
};

// 13
void CGameServerClient::pressStart(irr::c8 *data)
{
	CPPressStart* ps = new CPPressStart(data, this);
	CharId = CharSelectIds.CharIds[ps->CharIndex];
};

// 14
void CGameServerClient::createCharButtion(irr::c8* data)
{
	// Empty packet.
	sendPacket(new CPCharTemplate());
};

// 15
void CGameServerClient::requestItemList(irr::c8* data)
{
	sendPacket(new CSPItemList(true));
};

// 56
void CGameServerClient::clientSay(irr::c8* data)
{
	new CCPSay(data, this);
};

// 72
void CGameServerClient::validatePosition(irr::c8* data)
{
	// Validate Pos
};

// 157
void CGameServerClient::requestSkillCoolTime(irr::c8* data)
{
	// Ignore
};

// 208
void CGameServerClient::extendedPacket(irr::c8* data)
{
	printf("Recived unknown extended packet of type %d\n", (irr::u8)(data[1] & 0xff));
}

}
}
