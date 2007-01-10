/*
 * BDRSA.h - This is the BigDidgets RSA keygen/cipher modified into a c++ class.
 * Created Arpil 21, 2006, by Michael 'Bigcheese' Spencer.
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

#ifndef _BC_CLASS_BDRSA_
#define _BC_CLASS_BDRSA_

#include "bigd.h"

class BDRSA{
private:
	BIGD n, d, e;
public:
	BDRSA(int bits, unsigned long e);
	~BDRSA();

	void getMod(char* buff, int len);
	void encrypt(char* in, int in_len, char* out, int out_len);
	void decrypt(char* in, int in_len, char* out, int out_len);
};

#endif // #ifndef _BC_CLASS_BDRSA_
