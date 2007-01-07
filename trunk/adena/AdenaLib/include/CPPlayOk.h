/*
 * CPPlayOk.h - Play Ok ftw.
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

#ifndef _ADENA_C_P_PLAY_OK_H_
#define _ADENA_C_P_PLAY_OK_H_

#include <CLoginServerPacket.h>

namespace adena
{

	class CPPlayOk : public CLoginServerPacket
	{
	public:

		CPPlayOk(irr::s32 session_id)
		{
			w8(0x07);
			w32(session_id);
			w32(0x55667788);
		};

		virtual ~CPPlayOk()
		{

		};

		virtual irr::c8* getData()
		{
			blowfishPad();
			return Data;
		};

		virtual irr::u32 getLen()
		{
			return WritePointer;
		};

	};

}

#endif
