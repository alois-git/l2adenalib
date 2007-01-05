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

#include <string>
/**
 * This file is based on the Blowfish Engine that is part of 
 * the BouncyCastle JCE
 * 
 * Copyright (c) 2000 The Legion Of The Bouncy Castle (http://www.bouncycastle.org)
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies 
 * or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _BLOWFISH_
#define _BLOWFISH_

#define ROUNDS 16
#define BLOCK_SIZE 8 // bytes = 64 bits
#define SBOX_SK  256
#define P_SZ ROUNDS + 2

class BlowfishEngine
{
private:
	int *P;
	int S0[SBOX_SK];
	int S1[SBOX_SK];
	int S2[SBOX_SK];
	int S3[SBOX_SK];
	/*
	int *KS1;
	 int* KS2;
	 int *KS3;*/
	//====================================
	// Useful constants
	//====================================
	/*int * S0,* S1,* S2,* S3,* P; 	*/
	bool encrypting;
	char workingKey[50];
public:
	BlowfishEngine();
	/**
	 * initialise a Blowfish cipher.
	 * 
	 * @param forEncryption
	 *            whether or not we are for encryption.
	 * @param params
	 *            the parameters required to set up the cipher.
	 * @exception IllegalArgumentException
	 *                if the params argument is inappropriate.
	 */
	void init(bool encrypting, char key[]);
	char* getAlgorithmName();
	int processBlock(char in[], int inOff, char *out, int outOff);
	void reset();
	int getBlockSize();
	//==================================
	// Private Implementation
	//==================================
private:
	int F(int x);
	/**
	 * apply the encryption cycle to each value pair in the table.
	 */
	void processTable(int xl, int xr, int *table, int size );
	void setKey(char key[]);
	
	/**
	 * Encrypt the given input starting at the given offset and place the
	 * result in the provided buffer starting at the given offset. The input
	 * will be an exact multiple of our blocksize.
	 */
	void encryptBlock(char src[], int srcIndex, char *dst, int dstIndex);
	/**
	 * Decrypt the given input starting at the given offset and place the
	 * result in the provided buffer starting at the given offset. The input
	 * will be an exact multiple of our blocksize.
	 */
	void decryptBlock(char src[], int srcIndex, char *dst, int dstIndex);
	int BytesTo32bits(char b[], int i);
	void Bits32ToBytes(int in, char *b[], int offset);
};

#endif // #ifndef _BLOWFISH_
