/*
 * CPLoginFailed.h - login failed responce.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_P_LOGIN_FAILED_H_
#define _ADENA_C_P_LOGIN_FAILED_H_

#include <CLoginServerPacket.h>

namespace adena
{

	class CPLoginFailed : public CLoginServerPacket
	{
	public:
		const static int REASON_ACCOUNT_BANNED = 0x09;
		// 8: Access failed.
		const static int REASON_ACCOUNT_IN_USE = 0x07;
		// 6: Access failed.
		// 5: Your account information is incorrect. For more details, please contatct our blah blah blah...
		const static int REASON_ACCESS_FAILED = 0x04;
		const static int REASON_USER_OR_PASS_WRONG = 0x03;
		const static int REASON_PASS_WRONG = 0x02;
		const static int REASON_SYSTEM_ERROR = 0x01;

		CPLoginFailed(irr::s32 reason)
		{
			w8(0x01);
			w32(reason);
		};

		virtual ~CPLoginFailed()
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
