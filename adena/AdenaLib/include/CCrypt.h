/*
 * CCrypt.h - L2's usless xor encryption...
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

#ifndef _ADENA_C_CRYPT_H_
#define _ADENA_C_CRYPT_H_

#include <AdenaConfig.h>
#include <memory.h>

namespace adena
{
namespace game_server
{

	class ADENALIB_API CCrypt
	{
	public:

		CCrypt(irr::c8* key);

		~CCrypt();

		void decrypt(irr::c8* data, irr::u32 len);

		void encrypt(irr::c8* data, irr::u32 len);

		const irr::c8* getKey();

	private: 

		irr::c8 Key[8];

	};

}
}

#endif
