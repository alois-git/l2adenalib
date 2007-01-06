/*
 * IHash.h - Hasher interface.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_HASH_H_INCLUDED__
#define __IRR_HASH_H_INCLUDED__

#include <IKey.h>
#include <IKeyParms.h>
#include <ECipherRet.h>
#include <irrTypes.h>
#include <irrList.h>
#include <irrString.h>

namespace irr
{
namespace crypt
{

	class IHash
	{
	public:

		virtual ~IHash() {}

		virtual void getHashSizes(core::list<u32>* sizes) = 0;

		virtual ECRYPT_Cipher_Ret hash_start() = 0;

		virtual ECRYPT_Cipher_Ret hash_append(u8* in, u32 in_size) = 0;

		virtual ECRYPT_Cipher_Ret hash_finish(u8* out, u32 out_size) = 0;

		virtual core::stringc quickHash(core::stringc str) = 0;
	};

}
}

#endif
