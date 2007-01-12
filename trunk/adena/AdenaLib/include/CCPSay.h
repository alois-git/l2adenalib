/*
 * CCPSay.h - Client chat
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

#ifndef _ADENA_C_C_P_SAY_H_
#define _ADENA_C_C_P_SAY_H_

#include <CClientPacket.h>
#include <irrString.h>
#include <CSPCreatureSay.h>

namespace adena
{
namespace game_server
{

	enum E_SAY_TYPE
	{
		EST_ALL = 0,
		EST_SHOUT = 1, //!
		EST_TELL = 2,
		EST_PARTY = 3, //#
		EST_CLAN = 4,  //@
		EST_GM = 5,    
		EST_PETITION_PLAYER = 6, // used for petition
		EST_PETITION_GM = 7, //* used for petition
		EST_TRADE = 8, //+
		EST_ALLIANCE = 9, //$
		EST_ANNOUNCEMENT = 10,
		EST_PARTYROOM_ALL = 15, //(yellow)
		EST_PARTYROOM_COMMANDER = 16, //(blue)
		EST_HERO_VOICE = 17
	};

	class CCPSay : public CClientPacket
	{
	public:

		CCPSay(irr::c8* in_data, IGameServerClient* client)
		: CClientPacket()
		{
			Client = client;
			Data = in_data;
			ReadPointer++;
			rStrW(Message);
			Type = (E_SAY_TYPE)r32();
			if(Type == EST_TELL)
				rStrW(Target);
			start();
		};

		virtual ~CCPSay()
		{
			Data = 0;
		};

		virtual void run()
		{
			//Client->s
			AVL<irr::u32, COPawn*>::Iterator<irr::u32, COPawn*> ittr(&Client->Server->Players);
			irr::u32 key;
			COPawn* item;
			if(ittr.GetFirst(key, item))
			{
				CSPCreatureSay cs(Client->CharInfo->CharacterId, (irr::u32)Type, Client->CharInfo->Name, Message);
				while(true)
				{
					// Do stuff with item
					COPlayer* p = (COPlayer*)item;
					p->Client->sendPacket(&cs);
					if(!ittr.GetNext(key, item))
						break;
				}
			}
			delete this;
		};

		virtual irr::c8* getData()
		{
			return NULL;
		};

		virtual irr::u32 getLen()
		{
			return 0;
		};

		irr::core::stringc Message;
		irr::core::stringc Target;
		E_SAY_TYPE Type;

	};

}
}

#endif
