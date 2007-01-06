/*
 * CLoginServer.h - Login server.
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

#ifndef _ADENA_C_LOGIN_SERVER_H_
#define _ADENA_C_LOGIN_SERVER_H_

#include <AdenaConfig.h>
#include <irrThread.h>
#include <irrNet.h>
#include <irrDb.h>
#include <irrRng.h>
#include <BDRSA.h>
#include <CLoginServerNetEvent.h>
#include <NewCrypt.h>

namespace adena
{

	class ADENALIB_API CLoginServer : public irr::core::threads::Thread
	{
	public:

		/*
		 * @param addr: The address to bind to.
		 * result: Server is initalized and bound to addr.
		 * A RSA key is generated, scrambled and stored.
		 */
		CLoginServer(irr::net::Address &addr);

		virtual ~CLoginServer();

		virtual void run();

		char ScrambledMod[128];
		BDRSA* RsaCipher;
		NewCrypt* BlowfishCipher;
		irr::net::IServer* Server;
		irr::db::IDatabase* DataBase;
		irr::IRng* Rng;

	private:

		void ScrambleRsaPublicMod();
		NELoginServerNetEvent* EventParser;
		
	};
}

#endif
