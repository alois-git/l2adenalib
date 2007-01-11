/*
 * SGameServerInfo.h - Info about the game server requested by the login server.
 * Created January 10, 2006, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_S_GAME_SERVER_INFO_H_
#define _ADENA_S_GAME_SERVER_INFO_H_

#include <AdenaConfig.h>

namespace adena
{

	struct SGameServerInfo
	{
		irr::u32 ServerId;
		irr::u32 ConnectedClients;
		irr::u32 MaxClients;
		irr::c8 InternalIp[4];
		irr::c8 ExternalIp[4];
		irr::u16 Port;
	};

}

#endif
