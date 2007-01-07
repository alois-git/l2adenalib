/*
 * CHashMD5.h - MD5 hash interface.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <CHashMD5.h>
#include <stdio.h>

namespace irr
{
namespace crypt
{

CHashMD5::CHashMD5()
{

};

CHashMD5::~CHashMD5()
{

};

void CHashMD5::getHashSizes(core::list<u32> *sizes)
{
	sizes->push_back(128);
};

ECRYPT_Cipher_Ret CHashMD5::hash_start()
{
	md5_init(&State);
	return ECR_OK;
};

ECRYPT_Cipher_Ret CHashMD5::hash_append(u8 *in, u32 in_size)
{
	md5_append(&State, (const md5_byte_t *)in, in_size);
	return ECR_OK;
};

ECRYPT_Cipher_Ret CHashMD5::hash_finish(u8 *out, u32 out_size)
{
	if(out_size != 16)
		return ECR_FAILED;
	md5_finish(&State, out);
	return ECR_OK;
};

core::stringc CHashMD5::quickHash(core::stringc str)
{
	hash_start();
	hash_append((u8*)str.c_str(), str.size());
	u8 digest[16];
	hash_finish(digest, 16);
	c8 retstr[33];
	memset(retstr, 0, 33);
	c8* temp = retstr;
	for(int i = 0; i < 16; i++)
	{
		if((digest[i] & 0xff) > 0xf){
			sprintf(temp, "%x", (digest[i] & 0xff));
		}else{
			sprintf(temp, "0%x", (digest[i] & 0xff));
		}
		temp += 2;
	}
	core::stringc ret(retstr);
	return ret;
};

}
}
