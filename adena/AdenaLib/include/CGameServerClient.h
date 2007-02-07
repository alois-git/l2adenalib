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
#include <IGameServerClient.h>
#include <CPacketQueue.h>
#include <irrThread.h>

namespace adena
{
namespace game_server
{

	class CGameServerClient : public irr::core::threads::Thread, public IGameServerClient
	{
	friend CGameServer;
	public:

		typedef void (CGameServerClient::*packetFunc) (irr::c8*);

		CGameServerClient(irr::net::IServerClient* client, CGameServer* server);

		virtual ~CGameServerClient();

		virtual void run();

		void HandlePacket();

		virtual void sendPacket(IPacket* packet);

	protected:

		irr::c8* InBuff;
		irr::c8* OutBuff;

		CCrypt* OutputCipher;
		CCrypt* InputCipher;
		packetFunc PacketFunctions[256];
		CPacketQueue* PacketQueue;
		irr::u32 ProtocolRevision;

		void unknownPacket(irr::c8* data);

		// Funtions in order of their packet num starting at 0x00.
		void protocolVersion(irr::c8* data);		// 000 - 0x00
		void moveToLocation(irr::c8* data);			// 001 - 0x01
		void clientLoaded(irr::c8* data);			// 003 - 0x03
		void clickObj(irr::c8* data);				// 004 - 0x04
		void authLogin(irr::c8* data);				// 008 - 0x08
		void logout(irr::c8* data);					// 009 - 0x09
		void attack(irr::c8* data);					// 010 - 0x0a
		void createChar(irr::c8* data);				// 011 - 0x0b
		void pressStart(irr::c8* data);				// 013 - 0x0d
		void createCharButtion(irr::c8* data);		// 014 - 0x0e
		void requestItemList(irr::c8* data);		// 015 - 0x0f
		void requestSocial(irr::c8* data);			// 027 - 0x1b
		void requestUseSkill(irr::c8* data);		// 047 - 0x2f
		void clientSay(irr::c8* data);				// 056 - 0x38
		void requestSkillList(irr::c8* data);		// 063 - 0x3f
		void restartRequest(irr::c8* data);			// 070 - 0x46
		void validatePosition(irr::c8* data);		// 072 - 0x48
		void requestSkillCoolTime(irr::c8* data);	// 157 - 0x9d
		void requestMiniMap(irr::c8* data);			// 205 - 0xcd
		void extendedPacket(irr::c8* data);			// 208 - 0xd0
	};

}
}

#endif
