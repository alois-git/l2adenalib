/*
 * CPLoginOk.h - login ok responce.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_P_LOGIN_OK_H_
#define _ADENA_C_P_LOGIN_OK_H_

#include <CPacket.h>

namespace adena
{
namespace login_server
{

	class CPLoginOk : public CPacket
	{
	public:

		CPLoginOk(irr::s32 session_id)
		{
			w8(0x03);
			w32(session_id); // fist part of session id
			w32(session_id); // second part of session id
			w32(0x00);
			w32(0x00);
			w32(0x000003ea);
			w32(0x00);
			w32(0x00);
			w32(0x02);
		};

		virtual ~CPLoginOk()
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
}

#endif
