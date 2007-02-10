/*
 * CSPCreatureSay.h - Chat FTW.
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

#ifndef _ADENA_C_S_P_CREATURE_SAY_H_
#define _ADENA_C_S_P_CREATURE_SAY_H_

#include <CServerPacket.h>
#include <irrString.h>

namespace adena
{
namespace game_server
{

	class CSPCreatureSay : public CServerPacket
	{
	public:

		CSPCreatureSay(irr::u32 char_id, irr::u32 message_type, irr::core::stringc &messenger, irr::core::stringc &msg)
		: CServerPacket(), CharId(char_id), MessageType(message_type), Messenger(messenger), Message(msg)
		{
			Priority = EPP_LOW;
		};

		virtual ~CSPCreatureSay() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x4a);

				w32(CharId);
				w32(MessageType);
				wStrW(Messenger);
				wStrW(Message);
			}
			return true;
		};

		virtual irr::c8* getData()
		{
			return Data;
		};

		virtual irr::u32 getLen()
		{
			return WritePointer;
		};

	private:

		irr::u32 CharId;
		irr::u32 MessageType;
		irr::core::stringc Messenger;
		irr::core::stringc Message;

	};

}
}

#endif
