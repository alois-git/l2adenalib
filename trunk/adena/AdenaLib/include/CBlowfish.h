/*
 * CBlowfish.h - Blowfish wrapper with l2 checksum.
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


#ifndef _ADENA_C_BLOWFISH_H_
#define _ADENA_C_BLOWFISH_H_

#include <AdenaConfig.h>
#include "BlowfishEngine.h"

namespace adena
{

	class CBlowfish
	{
	public:

		CBlowfish(irr::c8* key)
		{
			Crypt = new BlowfishEngine();
			Crypt->init(true, key);
			Decrypt = new BlowfishEngine();
			Decrypt->init(false, key);
		}

		~CBlowfish()
		{
			delete Crypt;
			delete Decrypt;
		}

		bool checksum(irr::c8* data, irr::u32 data_len)
		{
			long chksum = 0;
			int count = data_len - 4;
			int i = 0;
			for (i = 0; i < count; i += 4)
			{
				long ecx = data[i] & 0xff;
				ecx |= (data[i + 1] << 8) & 0xff00;
				ecx |= (data[i + 2] << 0x10) & 0xff0000;
				ecx |= (data[i + 3] << 0x18) & 0xff000000;
				
				chksum ^= ecx;
			}

			long ecx = data[i] &0xff;
			ecx |= (data[i + 1] << 8) & 0xff00;
			ecx |= (data[i + 2] << 0x10) & 0xff0000;
			ecx |= (data[i + 3] << 0x18) & 0xff000000;

			data[i] = (irr::c8)chksum & 0xff;
			data[i + 1] = (irr::c8)(chksum >>0x08) & 0xff;
			data[i + 2] = (irr::c8)(chksum >>0x10) & 0xff;
			data[i + 3] = (irr::c8)(chksum >>0x18) & 0xff;

			return ecx == chksum;	
		}

		void decrypt(irr::c8* in_data, irr::u32 in_data_len, irr::c8* out_data, irr::u32 out_data_len)
		{
			int count = in_data_len /8;

			for (int i = 0; i < count; i++)
			{
				Decrypt->processBlock(in_data, i * 8, out_data, i * 8);
			}
		}

		void crypt(irr::c8* in_data, irr::u32 in_data_len, irr::c8* out_data, irr::u32 out_data_len)
		{
			int count = in_data_len / 8;
			if(in_data_len < 8)
			{
				count = 1;
			}

			for (int i = 0; i < count; i++)
			{
				Crypt->processBlock(in_data, i * 8, out_data, i * 8);
			}
		}

	private:

		BlowfishEngine *Crypt;
		BlowfishEngine *Decrypt;

	};

}

#endif
