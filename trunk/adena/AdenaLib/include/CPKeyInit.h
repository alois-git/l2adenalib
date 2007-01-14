/*
 * CPKeyInit.h - Send key to client.
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

#ifndef _ADENA_C_P_KEY_INIT_H_
#define _ADENA_C_P_KEY_INIT_H_

#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CPKeyInit : public CServerPacket
	{
	public:

		CPKeyInit(irr::c8* Key)
		: CServerPacket(), key(Key)
		{
			Priority = EPP_NORMAL;
			Crypt = false;
		};

		virtual ~CPKeyInit() {};

		virtual bool writePacket()
		{
			w8(0x00);
			w8(0x01);
			w8(key[0]);
			w8(key[1]);
			w8(key[2]);
			w8(key[3]);
			w8(key[4]);
			w8(key[5]);
			w8(key[6]);
			w8(key[7]);
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

		irr::c8* key;

	};

}
}

#endif
