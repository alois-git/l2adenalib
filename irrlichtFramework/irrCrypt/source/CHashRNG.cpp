/*
 * CHashRNG.h - Gets a random number, hashes it.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
 */

#include <CHashRNG.h>

namespace irr
{
namespace crypt
{

CHashRNG::CHashRNG(IRng* rng_array, u32 array_len, IHash* hasher)
: RngArray(rng_array), ArrayLen(array_len), Hasher(hasher)
{

};

CHashRNG::~CHashRNG()
{

};

void CHashRNG::seed(u32* seed, u32 seed_len)
{
	for(u32 i = 0; i < ArrayLen; i++)
		RngArray[i].seed(seed, seed_len);
};

u32 CHashRNG::getRandU32()
{
	u8 buff[16];
	Hasher->hash_start();
	u32 i;
	for(i = 0; i < ArrayLen; i++)
	{
		u32 temp = RngArray[i].getRandU32();
		Hasher->hash_append((u8*)&temp, 4);
	}
	Hasher->hash_finish(buff, 16);
	u32 ret = 0;
	for(i = 0; i < 16; i+=4)
	{
		u32 tmp;
		memcpy(&tmp, buff + i, 4);
		ret ^= tmp;
	}
	return ret;
};

s32 CHashRNG::getRandS32(s32 min, s32 max)
{
	s32 range = abs(min - max);
	u32 rand = getRandU32();
	rand %= range;
	return (rand + min);
};

void CHashRNG::getRandBuffer(c8 *buffer, u32 len)
{
	for(int i = 0; i < len; i++)
	{
		buffer[i] = getRandU32();
	}
};

}
}
