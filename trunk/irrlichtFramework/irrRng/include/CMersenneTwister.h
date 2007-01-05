/*
 * CMersenneTwister.h - Mersenne Twister RNG (NOT Cryptographicly secure).
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_MERSENNE_TWISTER_H_INCLUDED__
#define __IRR_MERSENNE_TWISTER_H_INCLUDED__

#include <irrRng.h>

#define N 624

namespace irr
{

	class IRRRNG_API CMersenneTwister : public IRng
	{
	public:

		CMersenneTwister();

		virtual ~CMersenneTwister();

		virtual void seed(u32* seed = NULL, u32 seed_len = 0);

		virtual u32 getRandU32();

		virtual s32 getRandS32(s32 min, s32 max);

		virtual void getRandBuffer(c8 *buffer, u32 len);

	private:

		unsigned long mt[N]; /* the array for the state vector  */
		int mti; /* mti==N+1 means mt[N] is not initialized */

	};

}

#endif
