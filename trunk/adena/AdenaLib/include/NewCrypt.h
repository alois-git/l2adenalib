/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

#ifndef _NEWCRYPT_
#define _NEWCRYPT_

#include "BlowfishEngine.h"
/**
 * This class ...
 * 
 * @version $Revision: 1.10 $ $Date: 2005/07/01 22:28:52 $
 */
class NewCrypt
{
	BlowfishEngine *_crypt;
	BlowfishEngine *_decrypt;
	
public:
	NewCrypt(char key[])
	{
		
		NewCrypt::_crypt = new BlowfishEngine();
		NewCrypt::_crypt->init(true, key);
		NewCrypt::_decrypt = new BlowfishEngine();
		NewCrypt::_decrypt->init(false, key);
	}
	
	bool checksum(char raw[], int so)
	{
		long chksum = 0;
		int count = so-4;
		int i =0;
		for (i=0; i<count; i+=4)
		{
			long ecx = raw[i] &0xff;
			ecx |= raw[i+1] << 8 &0xff00;
			ecx |= raw[i+2] << 0x10 &0xff0000;
			ecx |= raw[i+3] << 0x18 &0xff000000;
			
			chksum ^= ecx;
		}

		long ecx = raw[i] &0xff;
		ecx |= raw[i+1] << 8 &0xff00;
		ecx |= raw[i+2] << 0x10 &0xff0000;
		ecx |= raw[i+3] << 0x18 &0xff000000;

		raw[i] = chksum &0xff;
		raw[i+1] = chksum >>0x08 &0xff;
		raw[i+2] = chksum >>0x10 &0xff;
		raw[i+3] = chksum >>0x18 &0xff;

		return ecx == chksum;	
	}
	

	char* decrypt(char raw[], int so)
	{
		char *result = new char[so];
		int count = so /8;

		for (int i=0; i<count;i++)
		{
			NewCrypt::_decrypt->processBlock(raw,i*8,result,i*8);
		}

		return result;
	}
	
	char * crypt(char *raw, int so)
	{
		int count =  so /8;
		if(so < 8 )
		{
			count = 1;
		}
		char* result = new char[so];

		for (int i=0; i<count;i++)
		{
			NewCrypt::_crypt->processBlock(raw,i*8,result,i*8);
		}
		
		return result;
	}
};
/*
class NewDCrypt
{
	BlowfishEngine *_crypt33;
	BlowfishEngine *_decrypt;
	
public:
	NewDCrypt(char key[])
	{
		
		_crypt33 = new BlowfishEngine();
		/*_crypt33->init(true, key);*//*
		_decrypt = new BlowfishEngine();
		_decrypt->init(false, key);
	}
	
	bool checksum(char raw[], int so)
	{
		long chksum = 0;
		int count = so-8;
		int i =0;
		for (i=0; i<count; i+=4)
		{
			long ecx = raw[i] &0xff;
			ecx |= raw[i+1] << 8 &0xff00;
			ecx |= raw[i+2] << 0x10 &0xff0000;
			ecx |= raw[i+3] << 0x18 &0xff000000;
			
			chksum ^= ecx;
		}

		long ecx = raw[i] &0xff;
		ecx |= raw[i+1] << 8 &0xff00;
		ecx |= raw[i+2] << 0x10 &0xff0000;
		ecx |= raw[i+3] << 0x18 &0xff000000;

		raw[i] = (byte) (chksum &0xff);
		raw[i+1] = (byte) (chksum >>0x08 &0xff);
		raw[i+2] = (byte) (chksum >>0x10 &0xff);
		raw[i+3] = (byte) (chksum >>0x18 &0xff);

		return ecx == chksum;	
	}
	

	char* decrypt(char raw[], int so)
	{
		char *result = new char[so];
		int count = so /8;

		for (int i=0; i<count;i++)
		{
			_decrypt->processBlock(raw,i*8,result,i*8);
		}

		return result;
	}
	
	char * crypt(char raw[])
	{
		int count = sizeof(raw) /8;
		char* result = new char[sizeof(raw)];

		for (int i=0; i<count;i++)
		{
			_crypt33->processBlock(raw,i*8,result,i*8);
		}
		
		return result;
	}
};
*/

#endif
