/*
 * CInProcessGameServerLink.cpp - Loginserver -> Gameserver communication when in the same memory space.
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

#include <CInProcessGameServerLink.h>

namespace adena
{
namespace login_server
{

CInProcessGameServerLink::CInProcessGameServerLink(void* loginserver, void* loginserverlink)
{

};

CInProcessGameServerLink::~CInProcessGameServerLink()
{

};

void CInProcessGameServerLink::registerResult(irr::u32 server_id)
{
	
};

void CInProcessGameServerLink::requestKick(irr::u32 server_id, irr::u32 account_id)
{
	
};

// For CInProcessLoginServerLink

bool CInProcessGameServerLink::regServer(irr::u32 server_id)
{
	return true;
};

}
}
