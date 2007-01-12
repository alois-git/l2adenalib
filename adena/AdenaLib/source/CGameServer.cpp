/*
 * CGameServer.cpp - Game server.
 * Created January 6, 2006, by Michael 'Bigcheese' Spencer.
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

#include <CGameServer.h>
#include <ip2bytes.h>
#include <CMersenneTwister.h>
#include <CGameServerClient.h>

namespace adena
{
namespace game_server
{

CGameServer::CGameServer()
: Thread(), Server(0)
{
	memset(&Interfaces, 0, sizeof(Interfaces));
	Server = new irr::net::CTCPServer((irr::net::INetEvent*)this, 10);
};

CGameServer::~CGameServer()
{
	if(Server)
		delete Server;
	if(Interfaces.Logger)
		delete Interfaces.Logger;
};

void CGameServer::OnEvent(irr::net::NetEvent &e)
{
	switch(e.enet)
	{
		case irr::net::ENET_CLIENT_CONNECT:
			e.serverClient->UserData = new CGameServerClient(e.serverClient, this);
			break;
		case irr::net::ENET_CLIENT_DISCONNECT:
			if(((CGameServerClient*)e.serverClient->UserData)->AccountId != 0)
			{
				
			}
			delete ((CGameServerClient*)e.serverClient->UserData);
			break;
		case ::irr::net::ENET_RECVDATA:
			((CGameServerClient*)e.serverClient->UserData)->HandlePacket();
			break;
	}
};

void CGameServer::loginLinkEvent(SLoginLinkEvent e)
{
	if(e.EventType == ELLET_REGISTER_RESULT)
	{
		if(e.Result == ELLR_OK)
		{
			Interfaces.Logger->log("Connected to login server");
		}else
		{
			Interfaces.Logger->log("Failed to connect to login server");
		}
	}else if(e.EventType == ELLET_REQUEST_SERVER_INFO)
	{
		e.RequestServerInfo.ServerInfo->ConnectedClients = 0;
		e.RequestServerInfo.ServerInfo->MaxClients = 100;
		e.RequestServerInfo.ServerInfo->ServerId = 0;

		e.RequestServerInfo.ServerInfo->Port = atoi((*Interfaces.ConfigFile)["gameserver"]["port"].getData());

		irr::c8 ip[4];
		ip2bytes((*Interfaces.ConfigFile)["gameserver"]["external_host"].getData(), ip);
		memcpy(e.RequestServerInfo.ServerInfo->ExternalIp, ip, 4);
		ip2bytes((*Interfaces.ConfigFile)["gameserver"]["internal_host"].getData(), ip);
		memcpy(e.RequestServerInfo.ServerInfo->InternalIp, ip, 4);
	}else if(e.EventType == ELLET_PLAY_REQUEST)
	{
		SAccountUser au;
		au.AccountId = e.PlayRequest.AccountId;
		au.SessionId = e.PlayRequest.SessionId;

		WaitingToLoginMutex.getLock();
		WaitingToLogin.Insert(e.PlayRequest.AccountName, au);
		WaitingToLoginMutex.releaseLock();
	}
};

bool CGameServer::init(const char* config_file)
{	
	if(Interfaces.Logger == 0)
		Interfaces.Logger = new irr::CLogger(NULL);

	try
	{
		Interfaces.ConfigFile = new BCini(config_file);
	}catch (std::exception e)
	{
		Interfaces.Logger->log(e.what());
		return false;
	}

	irr::net::Address a((*Interfaces.ConfigFile)["gameserver"]["internal_host"].getData(), (*Interfaces.ConfigFile)["gameserver"]["port"].getData());
	Server->bind(a);

	// Random number generator setup
	if(Interfaces.Rng == 0)
		Interfaces.Rng = new irr::CMersenneTwister();
	Interfaces.Rng->seed();

	// Database setup
	Interfaces.DataBase = new irr::db::CSQLLite();
	irr::db::CSQLLiteConParms qp = irr::db::CSQLLiteConParms();
	qp.FileName = (*Interfaces.ConfigFile)["sqlite"]["file"].getData();
	Interfaces.Logger->log("Attempting to connect to DB...");
	if(!Interfaces.DataBase->connect(&qp))
	{
		Interfaces.Logger->log("FATAL ERROR: Failed to connect to DB (Check connection settings)", irr::ELL_ERROR);
		return false;
	}else
		Interfaces.Logger->log("DB connection sucsessfull");

	// Register with login server
	LoginServerLink->registerWithLoginServer();

	// Create caches
	Interfaces.PlayerCache = new CPlayerCache(&Interfaces);
	Interfaces.CharTemplates = new CCharTemplates(Interfaces.DataBase);

	return true;
};


void CGameServer::run()
{
	Server->start();
	Interfaces.Logger->log("Game Server up and running");
	while(Server->Running)
		irr::core::threads::sleep(1000);
};

}
}
