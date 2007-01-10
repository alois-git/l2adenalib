/*
 * CPRequestLogin.h - Client username and password.
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

#ifndef _ADENA_C_P_REQUEST_LOGIN_H_
#define _ADENA_C_P_REQUEST_LOGIN_H_

#include <CPacket.h>

namespace adena
{
namespace login_server
{

	class CPRequestLogin : public CPacket
	{
	public:

		CPRequestLogin(irr::c8* in_data, BDRSA* rsa)
		: CPacket()
		{
			irr::c8 dec[128];
			in_data ++; // Skip the packet type byte.
			rsa->decrypt(in_data, 128, dec, 128);
			irr::c8 user_buff[15];
			irr::c8 pass_buff[17];
			memcpy(user_buff, dec + 94, 14);
			memcpy(pass_buff, dec + 108, 16);
			user_buff[14] = 0;
			pass_buff[16] = 0;
			Username = irr::core::stringc(user_buff);
			Password = irr::core::stringc(pass_buff);
		};

		virtual ~CPRequestLogin()
		{
			
		};

		virtual irr::c8* getData()
		{
			return NULL;
		};

		virtual irr::u32 getLen()
		{
			return 0;
		};

		irr::core::stringc Username;

		irr::core::stringc Password;

	private:



	};

}
}

#endif
