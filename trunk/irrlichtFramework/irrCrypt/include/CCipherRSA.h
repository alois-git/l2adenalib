/*
 * CCipherRSA.h - RSA Cipher interface.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_CCIPHER_RSA_H_INCLUDED__
#define __IRR_CCIPHER_RSA_H_INCLUDED__

#include <ICipher.h>
#include <irrBigNum.h>
#include <irrCryptCompile.h>
#include <irrTypes.h>

namespace irr
{
namespace crypt
{

	class IRRCRYPT_API CKeyParmsRSA : public IKeyParms
	{
	public:

		//! \parm nbits: key bits.
		//! \parm e: Public exponent e.
		CKeyParmsRSA(u32 nbits, math::BigNum &e);

		virtual ~CKeyParmsRSA();

		u32 bits;
		math::BigNum e;

	};

	class IRRCRYPT_API CKeyRSA : public IKey
	{
	public:

		CKeyRSA();

		virtual ~CKeyRSA();

		virtual ByteStream<>* serialize();

		virtual void deserialize(ByteStream<> &bs);

		u32 bits;

		//! Public modulus.
		math::BigNum n;

		//! Public exponent.
		math::BigNum e;

		//! Private exponent.
		math::BigNum d;

	};

	class IRRCRYPT_API CCipherRSA : public ICipher
	{
	public:

		CCipherRSA();

		virtual ~CCipherRSA();

		virtual ECRYPT_Cipher_Ret encrypt(u8* in, u32 in_size, u8* out, u32 out_size);

		virtual ECRYPT_Cipher_Ret decrypt(u8* in, u32 in_size, u8* out, u32 out_size);

		virtual IKey* generateKey(IKeyParms* parms, IRng* rng = NULL);

		virtual IKey* getKey();

		virtual ECRYPT_Cipher_Ret setKey(IKey* key);

	private:
	};

}
}

#endif
