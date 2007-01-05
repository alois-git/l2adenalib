/*
 * CDefaultRNG.cpp - Default random number generator.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <CDefaultRNG.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

namespace irr
{

CDefaultRNG::CDefaultRNG()
{
	srand(time(NULL));
};

CDefaultRNG::~CDefaultRNG()
{

};

void CDefaultRNG::seed(u32* seed, u32 seed_len)
{
	if(seed == NULL)
		srand(time(NULL));
	else
		srand(seed[0]);
};

u32 CDefaultRNG::getRandU32()
{
	return rand();
};

s32 CDefaultRNG::getRandS32(s32 min, s32 max)
{
	s32 range = abs(min - max);
	u32 rand = getRandU32();
	rand %= range;
	return (rand + min);
};

void CDefaultRNG::getRandBuffer(c8 *buffer, u32 len)
{
	for(int i = 0; i < len; i++)
	{
		buffer[i] = getRandU32();
	}
};

}
