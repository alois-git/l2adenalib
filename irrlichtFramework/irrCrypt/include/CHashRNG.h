/*
 * CHashRNG.h - Gets a random number, hashes it.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_HASH_RNG_H_INCLUDED__
#define __IRR_HASH_RNG_H_INCLUDED__

#include <irrRng.h>
#include <IHash.h>

namespace irr
{
namespace crypt
{

	class IRRRNG_API CHashRNG : public IRng
	{
	public:

		CHashRNG(IRng* rng_array, u32 array_len, IHash* hasher);

		virtual ~CHashRNG();

		virtual void seed(u32* seed = NULL, u32 seed_len = 0);

		virtual u32 getRandU32();

		virtual s32 getRandS32(s32 min, s32 max);

		virtual void getRandBuffer(c8 *buffer, u32 len);

	private:

		IRng* RngArray;
		u32 ArrayLen;
		IHash* Hasher;

	};

}
}

#endif
