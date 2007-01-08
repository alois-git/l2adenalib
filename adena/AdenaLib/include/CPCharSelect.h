/*
 * CPCharSelect.h - Send key to client.
 * Created January 7, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_P_CHAR_SELECT_H_
#define _ADENA_C_P_CHAR_SELECT_H_

#include <CPacket.h>

namespace adena
{
namespace game_server
{

	class CPCharSelect : public CPacket
	{
	public:

		CPCharSelect()
		: CPacket()
		{
			w8(0x13);
			w32(1);

			wStrW(irr::core::stringw("bigcheese"));
			w32(0x01); // ?
			wStrW(irr::core::stringw("bigcheese"));
			w32(0x01);
			w32(0x00);
			w32(0x00); // ??

			w32(0x01);
			w32(0x00);

			w32(13);

			w32(0x01); // active

			w32(0x00); // x
			w32(0x00); // y
			w32(0x00); // z

			w32(50); // hp cur
			w32(50); // mp cur

			w32(0);
			w32(20);
			w32(80);

			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);

			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);

			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);
			w32(0x00);

			w32(0x00);
			w32(0x00);
			w32(0x00);

			w32(100); // hp max
			w32(100); // mp max

			w32(0x00); // days left before
											// delete .. if != 0
											// then char is inactive
			w32(0x00);
			w32(0x00); //c3 auto-select char

			w8(0x00);
		};

		virtual ~CPCharSelect()
		{

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



	};

}
}

#endif
