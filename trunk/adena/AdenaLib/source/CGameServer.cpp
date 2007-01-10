/*
 * CGameServer.cpp - Game server.
 * Created January 6, 2006, by Michael 'Bigcheese' Spencer.
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

#include <CGameServer.h>
#include <CLogger.h>
#include <ip2bytes.h>
#include <CMersenneTwister.h>

namespace adena
{
namespace game_server
{

CGameServer::CGameServer()
: Thread(), Server(0)
{
	memset(&Interfaces, 0, sizeof(Interfaces));
	EventParser = new NEGameServerNetEvent(this);
	Server = new irr::net::CTCPServer(EventParser, 10);

};

CGameServer::~CGameServer()
{
	if(Server)
		delete Server;
	if(Interfaces.Logger)
		delete Interfaces.Logger;
	delete EventParser;
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
	irr::c8 ip[4];
	ip2bytes((*Interfaces.ConfigFile)["gameserver"]["external_host"].getData(), ip);
	LoginServerLink->registerWithLoginServer(ip, atoi((*Interfaces.ConfigFile)["gameserver"]["port"].getData()));
	return true;
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
	}
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
