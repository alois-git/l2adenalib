/*
 * CLoginServer.cpp - Login server.
 * Created December 31, 2006, by Michael 'Bigcheese' Spencer.
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

#include <CLoginServer.h>
#include <CMersenneTwister.h>

namespace adena
{

CLoginServer::CLoginServer(irr::net::Address &addr)
: Thread()
{
	Rng = new irr::CMersenneTwister();
	EventParser = new NELoginServerNetEvent(this);
	Server = new irr::net::CTCPServer(EventParser, 10);
	Server->bind(addr);
	RsaCipher = new BDRSA(1024, 65537);
	RsaCipher->getMod(ScrambledMod, 128);
	ScrambleRsaPublicMod();
	BlowfishCipher = new NewCrypt("_;5.]94-31==-%xT!^[$\000");
	DataBase = new irr::db::CSQLLite();
	irr::db::CSQLLiteConParms qp = irr::db::CSQLLiteConParms();
	qp.FileName = "l2login.sqlite";
	if(!DataBase->connect(&qp))
		puts("database connection failed");
};

CLoginServer::~CLoginServer()
{
	delete Server;
	delete EventParser;
	delete RsaCipher;
	delete BlowfishCipher;
};

void CLoginServer::run()
{
	Server->start();
	while(Server->Running)
		irr::core::threads::sleep(1000);
};

void CLoginServer::ScrambleRsaPublicMod()
{
	// Scramble code from l2j.
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
