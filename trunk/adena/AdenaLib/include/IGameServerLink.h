/*
 * IGameServerLink.h - Loginserver -> Gameserver communication.
 * Created January 8, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_I_GAME_SERVER_LINK_H_
#define _ADENA_I_GAME_SERVER_LINK_H_

#include <AdenaConfig.h>

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
		EGLET_REGISTER_REQUEST = 0
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
		void* Data;
	};

	class IGameServerLink
	{
	public:

		virtual ~IGameServerLink() {}

		virtual void registerResult(irr::u32 server_id) = 0;

		virtual void requestKick(irr::u32 server_id, irr::u32 account_id) = 0;

	private:

	};

}
}

#endif
