/*
 * IGameServerLink.h - Loginserver -> Gameserver communication.
 * Created January 8, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_I_GAME_SERVER_LINK_H_
#define _ADENA_I_GAME_SERVER_LINK_H_

#include <AdenaConfig.h>
#include <SGameServerInfo.h>
#include <irrString.h>

namespace adena
{
namespace login_server
{

	/*
	 * This class allows us to hide the interface used between the login server and game server.
	 * All calls are async
	 */

	enum E_GameLinkEventType
	{
		EGLET_REGISTER_REQUEST = 0,
		EGLET_CLIENT_DROPED,
		EGLET_SERVER_INFO
	};

	enum E_GameLinkResult
	{
		EGLR_OK = 0,
		EGLR_GAME_SERVER_DOWN
	};

	struct SGameLinkEvent
	{
		E_GameLinkEventType EventType;
		E_GameLinkResult Result;
		irr::u32 ServerId;

		union
		{
			struct
			{
				irr::c8 Ip[4];
				irr::u16 Port;
			} RegisterRequest;

			struct
			{
				irr::u32 AccountId;
			} ClientDroped;

			struct
			{
				SGameServerInfo GameServerInfo;
			} ServerInfo;
		};
	};

	class IGameServerLink
	{
	public:

		virtual ~IGameServerLink() {}

		/*
		 * @param server_id: Index of the server (0 base what shows on the server list) to request from.
		 * @param account_id: Account id of the client to disconnect.
		 */
		virtual void requestKick(irr::u32 server_id, irr::u32 account_id) = 0;

		/*
		 * @param server_id: Index of the server (0 base what shows on the server list) to request from.
		 */
		virtual void requestServerInfo(irr::u32 server_id) = 0;

		/*
		 * @param server_id: Index of the server (0 base what shows on the server list) to request from.
		 * @param account_name: The name of the account, sent to game server by client.
		 * @param account_id: Account id of the client connecting.
		 * @param session_id: The client session id, sent to game server by client.
		 */
		virtual void requestPlay(irr::u32 server_id, irr::core::stringc account_name, irr::u32 account_id, irr::u32 session_id) = 0;

	private:

	};

}
}

#endif
