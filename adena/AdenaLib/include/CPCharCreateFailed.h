/*
 * CPCharCreateFailed.h - Char create failed.
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

#ifndef _ADENA_C_P_CHAR_CREATE_FAILED_H_
#define _ADENA_C_P_CHAR_CREATE_FAILED_H_

#include <CPacket.h>

namespace adena
{
namespace game_server
{

	class CPCharCreateFailed : public CPacket
	{
	public:

		static enum E_CharCreateFailedReason
		{
			ECCFR_CREATION_FAILED = 0x00,
			ECCFR_TOO_MANY_CHARACTERS = 0x01,
			ECCFR_NAME_ALREADY_EXISTS = 0x02,
			ECCFR_16_ENG_CHARS = 0x03
		};

		CPCharCreateFailed(E_CharCreateFailedReason reason)
		: CPacket()
		{
			w8(0x1a);
			w32((irr::u32)reason);
		};

		virtual ~CPCharCreateFailed()
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
