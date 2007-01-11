/*
 * CLoginServerClient.h - Login server client.
 * Created January 2, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_LOGIN_SERVER_CLIENT_H_
#define _ADENA_C_LOGIN_SERVER_CLIENT_H_

#include <AdenaConfig.h>
#include <irrNet.h>
#include <IPacket.h>
#include <CLoginServer.h>

namespace adena
{
namespace login_server
{

	class CLoginServerClient
	{
	public:

		CLoginServerClient(irr::net::IServerClient* client, CLoginServer* server);

		virtual ~CLoginServerClient();

		void HandlePacket();

		void SendPacket(IPacket* packet);

		irr::u32 AccountId;

	private:

		irr::net::IServerClient* Client;
		CLoginServer* Server;
		irr::s32 SessionId;
		irr::core::stringc AccountName;

	};

}
}

#endif
