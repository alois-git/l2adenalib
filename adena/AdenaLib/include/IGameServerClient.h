/*
 * IGameServerClient.h - Login server client interface (Because i need to beable to call sendpacket in packets).
 * Created January 11, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_I_GAME_SERVER_CLIENT_H_
#define _ADENA_I_GAME_SERVER_CLIENT_H_

#include <AdenaConfig.h>
#include <COObject.h>
#include <IPacket.h>
#include <irrNet.h>
#include <CGameServer.h>
#include <CCrypt.h>
#include <SCharInfo.h>
#include <CMemoryManager.h>

namespace adena
{
namespace game_server
{

	class IGameServerClient
	{
	friend CGameServer;
	public:

		virtual ~IGameServerClient() {}

		virtual void sendPacket(IPacket* packet) = 0;

		irr::net::IServerClient* Client;
		CGameServer* Server;
		irr::s32 SessionId;
		irr::core::stringc AccountName;
		irr::u32 AccountId;
		COObject* PController;
		SCharInfo* CharInfo;
		SCharSelectIds CharSelectIds;
		irr::u32 CharId;
		CMemoryManager MemoryManager;
	};

}
}

#endif
