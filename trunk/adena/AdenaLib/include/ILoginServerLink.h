/*
 * ILoginServerLink.h - Gameserver -> Loginserver communication.
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

#ifndef _ADENA_I_LOGIN_SERVER_LINK_H_
#define _ADENA_I_LOGIN_SERVER_LINK_H_

#include <AdenaConfig.h>
#include <SGameServerInfo.h>
#include <irrString.h>

namespace adena
{
namespace game_server
{

	/*
	 * This class allows us to hide the interface used between the login server and game server.
	 * All calls are async.
	 */

	enum E_LoginLinkEventType
	{
		ELLET_REGISTER_RESULT = 0,
		ELLET_REQUEST_SERVER_INFO,
		ELLET_PLAY_REQUEST
	};

	enum E_LoginLinkResult
	{
		ELLR_OK = 0,
		ELLR_LOGIN_SERVER_DOWN,
		ELLR_AUTH_FAILED
	};

	struct SLoginLinkEvent
	{
		E_LoginLinkEventType EventType;
		E_LoginLinkResult Result;

		struct
		{
			SGameServerInfo* ServerInfo;
		} RequestServerInfo;

		struct
		{
			irr::core::stringc AccountName;
			irr::u32 AccountId;
			irr::u32 SessionId;
		} PlayRequest;
		
	};

	class ILoginServerLink
	{
	public:

		virtual ~ILoginServerLink() {}

		virtual void registerWithLoginServer() = 0;

	private:

	};

}
}

#endif
