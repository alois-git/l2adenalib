/*
 * irrRng.h - Random number generator.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_RNG_H_INCLUDED__
#define __IRR_RNG_H_INCLUDED__

#include <irrCore.h>

#ifdef _IRR_WINDOWS_
#ifdef IRRRNG_EXPORTS
#define IRRRNG_API __declspec(dllexport)
#else
#define IRRRNG_API __declspec(dllimport)
#endif // IRRLICHT_EXPORT
#else
#define IRRRNG_API 
#endif // _IRR_WINDOWS_

namespace irr
{

	class IRng
	{
	public:

		virtual ~IRng() {}

		//! Must be called before calling any get functions.
		//! \param seed: Seeds the rng, if 0 uses an internal seed.
		//! \param seed_len: len of seed array.
		virtual void seed(u32* seed = NULL, u32 seed_len = 0) = 0;

		//! Gets one random u32.
		virtual u32 getRandU32() = 0;

		//! Gets one random s32 between min and max.
		virtual s32 getRandS32(s32 min, s32 max) = 0;

		//! Fills buffer of size len with random data.
		//! \param buffer: buffer to be filled.
		//! \param len: length of buffer.
		virtual void getRandBuffer(c8 *buffer, u32 len) = 0;

	};

}

#endif