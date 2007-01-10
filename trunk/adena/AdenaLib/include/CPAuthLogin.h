/*
 * CPAuthLogin.h - Authenticate login.
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

#ifndef _ADENA_C_P_AUTH_LOGIN_H_
#define _ADENA_C_P_AUTH_LOGIN_H_

#include <CPacket.h>
#include <irrString.h>

namespace adena
{
namespace game_server
{

	class CPAuthLogin : public CPacket
	{
	public:

		CPAuthLogin(irr::c8* in_data)
		: CPacket(), AccountName("")
		{
			Data = in_data;
			ReadPointer++;
			rStrW(AccountName);
			Id1 = r32();
			Id2 = r32();
			Id3 = r32();
			Id4 = r32();
		};

		virtual ~CPAuthLogin()
		{
			Data = 0;
		};

		virtual irr::c8* getData()
		{
			return NULL;
		};

		virtual irr::u32 getLen()
		{
			return 0;
		};

		irr::core::stringc AccountName;
		irr::u32 Id1; // Corrupt 2nd key. first 2 bytes are always wrong.
		irr::u32 Id2; // sesionId given at PlayOk.
		irr::u32 Id3; // sesionId given at LoginOk.
		irr::u32 Id4; // sesionId given at LoginOk.

	private:



	};

}
}

#endif
