/*
 * CHashMD5.h - MD5 hash interface.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_HASH_MD5_H_INCLUDED__
#define __IRR_HASH_MD5_H_INCLUDED__

#include <IHash.h>
#include <irrCryptCompile.h>
#include <irrTypes.h>
#include <irrString.h>
#include <md5.h>

namespace irr
{
namespace crypt
{

	class IRRCRYPT_API CHashMD5 : public IHash
	{
	public:

		CHashMD5();
		
		virtual ~CHashMD5();

		virtual void getHashSizes(core::list<u32> *sizes);

		virtual ECRYPT_Cipher_Ret hash_start();

		virtual ECRYPT_Cipher_Ret hash_append(u8* in, u32 in_size);

		virtual ECRYPT_Cipher_Ret hash_finish(u8* out, u32 out_size);

		virtual core::stringc quickHash(core::stringc str);

	private:

		md5_state_t State;

	};

}
}

#endif
