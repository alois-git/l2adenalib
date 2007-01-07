/*
 * CGameServerClient.h - Login server client.
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

#ifndef _ADENA_C_GAME_SERVER_CLIENT_H_
#define _ADENA_C_GAME_SERVER_CLIENT_H_

#include <AdenaConfig.h>
#include <irrNet.h>
#include <IPacket.h>
#include <CGameServer.h>
#include <CCrypt.h>

namespace adena
{

	class CGameServerClient
	{
	public:

		typedef void (CGameServerClient::*packetFunc) (irr::c8*);

		CGameServerClient(irr::net::IServerClient* client, CGameServer* server);

		virtual ~CGameServerClient();

		void HandlePacket();

		void SendPacket(IPacket* packet);

	private:

		CCrypt* OutputCipher;
		CCrypt* InputCipher;
		irr::net::IServerClient* Client;
		CGameServer* Server;
		irr::s32 SessionId;
		bool CryptPackets;
		packetFunc PacketFunctions[256];

	protected:

		void unknownPacket(irr::c8* data);

		// Funtions in order of their packet num starting at 0x00.
		void protocolVersion(irr::c8* data);

	};
}

#endif
