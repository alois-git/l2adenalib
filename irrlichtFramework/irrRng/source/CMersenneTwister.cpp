/*
 * CMersenneTwister.cpp - Default random number generator.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <CMersenneTwister.h>
#include <time.h>
#include <stdio.h>

/* Period parameters */  
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

namespace irr
{

CMersenneTwister::CMersenneTwister()
: mti(N+1)
{

};

CMersenneTwister::~CMersenneTwister()
{

};

void CMersenneTwister::seed(u32* seed, u32 seed_len)
{
	unsigned long s = 0;
	if(seed == NULL)
	{
		s = time(NULL);
	}else
	{
		if(seed_len == 1)
		{
			s = seed[0];
		}else
		{
			for(int i = 0; i < seed_len; i++)
			{
				s ^= seed[i];
			}
		}
	}
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
};

u32 CMersenneTwister::getRandU32()
{
	unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            seed(); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
};

s32 CMersenneTwister::getRandS32(s32 min, s32 max)
{
	s32 range = abs(min - max);
	u32 rand = getRandU32();
	rand %= range;
	return (rand + min);
};

void CMersenneTwister::getRandBuffer(c8 *buffer, u32 len)
{
	for(int i = 0; i < len; i+= 4)
	{
		u32 rand = getRandU32();
		if((len - i) > 4)
			memcpy(&buffer[i], &rand, 4);
		else
			memcpy(&buffer[i], &rand, len - i);
	}
};

}
