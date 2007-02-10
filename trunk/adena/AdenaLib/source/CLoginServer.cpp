/*
 * CLoginServer.cpp - Login server.
 * Created December 31, 2006, by Michael 'Bigcheese' Spencer.
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

#include <CLoginServer.h>
#include <CMersenneTwister.h>
#include <IGameServerLink.h>
#include <CLogger.h>

namespace adena
{
namespace login_server
{

CLoginServer::CLoginServer()
: Thread(),  Server(0)
{
	memset(&Interfaces, 0, sizeof(Interfaces));
	EventParser = new NELoginServerNetEvent(this);
	Server = new irr::net::CTCPServer(EventParser, 10);

	InternalServerListPacket = new CPServerList();
	ExternalServerListPacket = new CPServerList();
};

CLoginServer::~CLoginServer()
{
	if(Server)
		delete Server;
	if(Interfaces.Logger)
		delete Interfaces.Logger;
	delete EventParser;
	delete Interfaces.RsaCipher;
	delete Interfaces.BlowfishCipher;
};

bool CLoginServer::init(const char* config_file)
{
	if(Interfaces.Logger == 0)
		Interfaces.Logger = new irr::CLogger(NULL);

	Interfaces.ConfigFile = new CConfig(config_file);

	irr::net::Address a(Interfaces.ConfigFile->getString("loginserver", "host"), Interfaces.ConfigFile->getString("loginserver", "port"));
	Server->bind(a);

	// Random number generator setup
	if(Interfaces.Rng == 0)
		Interfaces.Rng = new irr::CMersenneTwister();
	Interfaces.Rng->seed();

	// Rsa setup
	Interfaces.Logger->log("Generating RSA key...");
	Interfaces.RsaCipher = new BDRSA(1024, 65537);
	Interfaces.RsaCipher->getMod(ScrambledMod, 128);
	ScrambleRsaPublicMod();
	Interfaces.Logger->log("RSA key generated and scrambled");

	// Blowfish setup
	Interfaces.BlowfishCipher = new CBlowfish("_;5.]94-31==-%xT!^[$\000");

	// Database setup
	irr::db::IDbConParms* conp;
	if(!strcmp("mysql" ,Interfaces.ConfigFile->getString("database", "type").c_str()))
	{
		Interfaces.DataBase = new irr::db::CMySQL();
		irr::db::CMySQLConParms* cp = new irr::db::CMySQLConParms();
		cp->Ip = Interfaces.ConfigFile->getString("mysql", "ip");
		cp->Username = Interfaces.ConfigFile->getString("mysql", "username");
		cp->Password = Interfaces.ConfigFile->getString("mysql", "password");
		cp->Db = Interfaces.ConfigFile->getString("mysql", "db");
		cp->Port = Interfaces.ConfigFile->getInt("mysql", "port");
		conp = cp;
	}else
	{
		Interfaces.DataBase = new irr::db::CSQLLite();
		irr::db::CSQLLiteConParms* qp = new irr::db::CSQLLiteConParms();
		qp->FileName = Interfaces.ConfigFile->getString("sqlite", "file");
		conp = qp;
	}
	Interfaces.Logger->log("Attempting to connect to DB...");
	if(!Interfaces.DataBase->connect(conp))
	{
		Interfaces.Logger->log("FATAL ERROR: Failed to connect to DB (Check connection settings)", irr::ELL_ERROR);
		return false;
	}else
		Interfaces.Logger->log("DB connection sucsessfull");

	delete conp;

	return true;
};

void CLoginServer::gameLinkEvent(SGameLinkEvent e)
{
	if(e.EventType == EGLET_REGISTER_REQUEST)
	{
		//ExternalServerListPacket->addServer(e.RegisterRequest.Ip, e.RegisterRequest.Port, true, false, 0, 1000, false, true, 1, e.ServerId);
		GameServerLink->requestServerInfo(e.ServerId);
	}else if(e.EventType == EGLET_SERVER_INFO)
	{
		ExternalServerListPacket->addServer(e.ServerInfo.GameServerInfo.ExternalIp, e.ServerInfo.GameServerInfo.Port, true, false, 0, 1000, false, true, 1, e.ServerId);
		InternalServerListPacket->addServer(e.ServerInfo.GameServerInfo.InternalIp, e.ServerInfo.GameServerInfo.Port, true, false, 0, 1000, false, true, 1, e.ServerId);
	}
};

void CLoginServer::run()
{
	Server->start();
	Interfaces.Logger->log("Login Server up and awaiting connections");
	while(Server->Running)
		irr::core::threads::sleep(1000);
};

bool CLoginServer::loginAccount(irr::u32 account_id, irr::net::IServerClient* client)
{
	SAccountLocation al;
	AccountLocationsMutex.getLock();
	if(AccountLocations.Find(account_id, al))
	{
		if(al.Local == true)
		{
			AccountLocationsMutex.releaseLock();
			Server->kickClient(al.Data);
		}else
		{
			AccountLocationsMutex.releaseLock();
			GameServerLink->requestKick((irr::u32)al.Data, account_id);
		}
		return false;
	}else
	{
		al.Local = true;
		al.Data = client;
		AccountLocations.Insert(account_id, al);
		AccountLocationsMutex.releaseLock();
		return true;
	}
};

void CLoginServer::unlogAccount(irr::u32 account_id)
{
	AccountLocationsMutex.getLock();
	AccountLocations.Remove(account_id);
	AccountLocationsMutex.releaseLock();
};

SLoginServerStatus CLoginServer::getStatus()
{
	ServerStatus.UpTime = (irr::u32)(time(NULL) - StartTime);
	return ServerStatus;
};

void CLoginServer::ScrambleRsaPublicMod()
{
	char* n = ScrambledMod;
	int i;
	for (i = 0; i < 4; i++)
	{
		byte temp = n[0x00 + i];
		n[0x00 + i] = n[0x4d + i];
		n[0x4d + i] = temp;
	}

	// step 2 xor first 0x40 bytes with last 0x40 bytes
	for (i = 0; i < 0x40; i++)
	{
		n[i] = (byte)(n[i] ^ n[0x40 + i]);
	}

	// step 3 xor bytes 0x0d-0x10 with bytes 0x34-0x38
	for (i = 0; i < 4; i++)
	{
		n[0x0d + i] = (byte)(n[0x0d + i] ^ n[0x34 + i]);
	}

	// step 4 xor last 0x40 bytes with first 0x40 bytes
	for (i = 0; i < 0x40; i++)
	{
		n[0x40 + i] = (byte)(n[0x40 + i] ^ n[i]);
	}
};

}
}
