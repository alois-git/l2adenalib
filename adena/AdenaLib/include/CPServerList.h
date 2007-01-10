/*
 * CPServerList.h - Teh server list.
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

#ifndef _ADENA_C_P_SERVER_LIST_H_
#define _ADENA_C_P_SERVER_LIST_H_

#include <CPacket.h>
#include <irrList.h>

namespace adena
{
namespace login_server
{

	class CPServerList : public CPacket
	{
	public:

		struct ServerNode
		{
			irr::c8 ip[4];
			irr::u16 port;
			bool pvp;
			bool testServer;
			irr::u32 currentPlayers;
			irr::u32 maxPlayers;
			bool brackets;
			bool clock;
			irr::u32 status;
			irr::u32 server_id;
		};

		bool ListNeedsCreation;
		irr::core::list<ServerNode> ServerNodeList;

		CPServerList()
		: ListNeedsCreation(true)
		{
			ServerNodeList = irr::core::list<ServerNode>();
		};

		virtual ~CPServerList()
		{

		};

		virtual void addServer(irr::c8 ip[4], irr::u16 port, bool pvp, bool testServer, irr::u32 currentPlayers, irr::u32 maxPlayers, bool brackets, bool clock, irr::u32 status, irr::u32 server_id)
		{
			ServerNode sn;
			memcpy(sn.ip, ip, 4);
			sn.port = port;
			sn.pvp = pvp;
			sn.testServer = testServer;
			sn.currentPlayers = currentPlayers;
			sn.maxPlayers = maxPlayers;
			sn.brackets = brackets;
			sn.clock = clock;
			sn.status = status;
			sn.server_id = server_id;
			ServerNodeList.push_back(sn);
			ListNeedsCreation = true;
		};

		virtual irr::c8* getData()
		{
			if(ListNeedsCreation)
			{
				// Go back to beginning of data.
				WritePointer = 0;

				w8(0x04);
				w8(ServerNodeList.getSize());
				w8(0x00);
				irr::core::list<ServerNode>::Iterator ittr;
				for(ittr = ServerNodeList.begin(); ittr != ServerNodeList.end(); ittr++)
				{
					w8((*ittr).server_id + 1);
					// Ip
					w8((*ittr).ip[0]);
					w8((*ittr).ip[1]);
					w8((*ittr).ip[2]);
					w8((*ittr).ip[3]);
					// Port
					w32((*ittr).port);
					// Age limit
					w8(0x0f);
					// Pvp?
					if((*ittr).pvp){
						w8(0x01);
					}else{
						w8(0x00);
					}
					// Player info
					w16((*ittr).currentPlayers);
					w16((*ittr).maxPlayers);
					if((*ittr).status == 0x00){ // Down
						w8(0x00);
					}else{ // Up
						w8(0x01);
					}
					int bits = 0;
					if((*ittr).testServer)
					{
						bits |= 0x04; 
					}
					if((*ittr).clock)
					{
						bits |= 0x02;
					}
					w32(bits);
					if((*ittr).brackets){
						w8(0x01);
					}else{
						w8(0x00);
					}
				}

				blowfishPad();
				ListNeedsCreation = false;
			}
			return Data;
		};

		virtual irr::u32 getLen()
		{
			return WritePointer;
		};

	};

}
}

#endif
