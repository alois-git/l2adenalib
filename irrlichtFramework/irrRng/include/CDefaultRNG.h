/*
 * CDefaultRNG.h - Default random number generator.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_DEFAULT_RNG_H_INCLUDED__
#define __IRR_DEFAULT_RNG_H_INCLUDED__

#include <irrRng.h>

namespace irr
{

	class IRRRNG_API CDefaultRNG : public IRng
	{
	public:

		CDefaultRNG();

		virtual ~CDefaultRNG();

		virtual void seed(u32* seed = NULL, u32 seed_len = 0);

		virtual u32 getRandU32();

		virtual s32 getRandS32(s32 min, s32 max);

		virtual void getRandBuffer(c8 *buffer, u32 len);

	};

}

#endif