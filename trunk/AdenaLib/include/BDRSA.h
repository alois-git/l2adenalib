/*
 * BDRSA.h - This is the BigDidgets RSA keygen/cipher modified into a c++ class.
 * Created Arpil 21, 2006, by Michael 'Bigcheese' Spencer.
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
