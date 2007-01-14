/*
 * CPCharCreateFailed.h - Char create failed.
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

#ifndef _ADENA_C_P_CHAR_CREATE_FAILED_H_
#define _ADENA_C_P_CHAR_CREATE_FAILED_H_

#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CPCharCreateFailed : public CServerPacket
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
		: CServerPacket(), Reason(reason)
		{
			Priority = EPP_NORMAL;
		};

		virtual ~CPCharCreateFailed()
		{

		};

		virtual bool writePacket()
		{
			w8(0x1a);
			w32((irr::u32)Reason);
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

		E_CharCreateFailedReason Reason;

	};

}
}

#endif
