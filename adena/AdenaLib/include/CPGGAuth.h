/*
 * CPGGAuth.h - Game gaurd authentication responce.
 * Created January 4, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_P_GG_AUTH_H_
#define _ADENA_C_P_GG_AUTH_H_

#include <CPacket.h>

namespace adena
{
namespace login_server
{

	class CPGGAuth : public CPacket
	{
	public:

		CPGGAuth()
		{
			w8(0x0b);
			w32(0x0b);
		};

		virtual ~CPGGAuth()
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
