/*
 * ECipherRet.h - Return values for ICipher and friends.
 * Created November 24, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_CIPHER_RET_H_INCLUDED__
#define __IRR_CIPHER_RET_H_INCLUDED__

namespace irr
{
namespace crypt
{

	enum ECRYPT_Cipher_Ret
	{
		//! Everything went ok.
		ECR_OK = 0,

		//! Failed.
		ECR_FAILED,
	};

}
}

#endif
