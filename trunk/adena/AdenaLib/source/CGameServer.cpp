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

namespace adena
{

CGameServer::CGameServer(irr::net::Address &addr)
: Thread(), Server(0)
{
	EventParser = new NEGameServerNetEvent(this);
	Server = new irr::net::CTCPServer(EventParser, 10);
	Server->bind(addr);
};

CGameServer::~CGameServer()
{
	if(Server)
		delete Server;
};

void CGameServer::run()
{
	Server->start();
	while(Server->Running)
		irr::core::threads::sleep(1000);
};

}
