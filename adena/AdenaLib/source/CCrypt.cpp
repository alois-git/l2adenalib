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

#include <CCrypt.h>

namespace adena
{
namespace game_server
{

CCrypt::CCrypt(irr::c8* key)
{
	memcpy(Key, key, sizeof(Key));
};

CCrypt::~CCrypt()
{

};

void CCrypt::decrypt(irr::c8* data, irr::u32 len)
{
	int temp = 0;
	for (irr::u32 i = 0; i < len; i++)
	{
		int temp2 = data[i] & 0xff;
		data[i] = (temp2 ^ (Key[i & 7] & 0xff) ^ temp);
		temp = temp2;
	}
	
	int old = Key[0] & 0xff;
	old |= (Key[1] << 0x08) & 0xff00;
	old |= (Key[2] << 0x10) & 0xff0000;
	old |= (Key[3] << 0x18) & 0xff000000;
	
	old += len;
	
	Key[0] = old &0xff;
	Key[1] = (old >> 0x08) & 0xff;
	Key[2] = (old >> 0x10) & 0xff;
	Key[3] = (old >> 0x18) & 0xff;
};

void CCrypt::encrypt(irr::c8* data, irr::u32 len){
	int temp = 0;
	for (irr::u32 i = 0; i < len; i++)	{
		int temp2 = data[i] & 0xff;
		data[i] = (temp2 ^ (Key[i & 7] & 0xff) ^ temp);
		temp = data[i];
	}
	
	int old = Key[0] & 0xff;
	old |= (Key[1] << 0x08) & 0xff00;
	old |= (Key[2] << 0x10) & 0xff0000;
	old |= (Key[3] << 0x18) & 0xff000000;
	
	old += len;
	
	Key[0] = old &0xff;
	Key[1] = (old >> 0x08) & 0xff;
	Key[2] = (old >> 0x10) & 0xff;
	Key[3] = (old >> 0x18) & 0xff;
};

const irr::c8* CCrypt::getKey(){
	return Key;
};

}
}
