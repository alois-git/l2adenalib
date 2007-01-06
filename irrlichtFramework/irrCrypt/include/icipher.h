/*
 * ICipher.h - Cypher interface.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_CIPHER_H_INCLUDED__
#define __IRR_CIPHER_H_INCLUDED__

#include <IKey.h>
#include <IKeyParms.h>
#include <ECipherRet.h>
#include <irrTypes.h>
#include <irrRng.h>

namespace irr
{
namespace crypt
{

	class ICipher
	{
	public:

		virtual ~ICipher(){}

		//! Encrypt function.
		//! \param in: buffer to be encrypted.
		//! \param in_size: size in bytes of in.
		//! \param out: buffer where encrypted data will go.
		//! \param out_size: size of out.
		virtual ECRYPT_Cipher_Ret encrypt(u8* in, u32 in_size, u8* out, u32 out_size) = 0;

		//! Decrypt function.
		//! \param in: buffer to be decrypted.
		//! \param in_size: size in bytes of in.
		//! \param out: buffer where decrypted data will go.
		//! \param out_size: size of out.
		virtual ECRYPT_Cipher_Ret decrypt(u8* in, u32 in_size, u8* out, u32 out_size) = 0;

		//! \param rng: random number generator, use default if null.
		virtual IKey* generateKey(IKeyParms* parms, IRng* rng = NULL) = 0;

		virtual IKey* getKey() = 0;

		virtual ECRYPT_Cipher_Ret setKey(IKey* key) = 0;

	protected:

		IKey* Key;

	};

}
}


#endif
