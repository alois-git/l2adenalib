/*
 * CGameServerClient.h - Login server client.
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

#ifndef _ADENA_C_GAME_SERVER_CLIENT_H_
#define _ADENA_C_GAME_SERVER_CLIENT_H_

#include <AdenaConfig.h>
#include <irrNet.h>
#include <IPacket.h>
#include <CGameServer.h>
#include <CCrypt.h>
#include <COPlayer.h>

namespace adena
{
namespace game_server
{

	class CGameServerClient
	{
	public:

		typedef void (CGameServerClient::*packetFunc) (irr::c8*);

		CGameServerClient(irr::net::IServerClient* client, CGameServer* server);

		virtual ~CGameServerClient();

		void HandlePacket();

		void sendPacket(IPacket* packet);

	private:

		CCrypt* OutputCipher;
		CCrypt* InputCipher;
		irr::net::IServerClient* Client;
		CGameServer* Server;
		irr::s32 SessionId;
		irr::core::stringc AccountName;
		bool CryptPackets;
		packetFunc PacketFunctions[256];
		COPlayer* Player;

	protected:

		void unknownPacket(irr::c8* data);

		// Funtions in order of their packet num starting at 0x00.
		void protocolVersion(irr::c8* data); // 0
		void clientLoaded(irr::c8* data); // 3
		void authLogin(irr::c8* data); // 8
		void logout(irr::c8* data); // 9
		void createChar(irr::c8* data); // 11
		void pressStart(irr::c8* data); // 13
		void createCharButtion(irr::c8* data); // 14

	};

}
}

#endif
