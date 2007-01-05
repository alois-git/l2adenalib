/*
 * irrBigNum.h - Large number class.
 * Created November 21, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_BIG_NUM_H_INCLUDED__
#define __IRR_BIG_NUM_H_INCLUDED__

#include <irrCore.h>
#include <irrRng.h>
#include <irrBigNumCompileConfig.h>

namespace irr
{
namespace math
{

	class IRRBIGNUM_API BigNum
	{
	public:

		BigNum(void);
		BigNum(BigNum &a);
		BigNum(u32 num);
		// decimal or hex with a 0x infront.
		BigNum(core::stringc &str);
		~BigNum();

		core::stringc ToStr(bool decimal = true);
		void print();

		BigNum& operator =(BigNum &a);
		BigNum& operator =(u32 num);
		// decimal or hex with a 0x infront.
		BigNum& operator =(core::stringc &str);

		bool operator ==(BigNum &a);
		bool operator != (BigNum &a);
		bool operator <(BigNum &a);
		bool operator >(BigNum &a);

		BigNum operator +(BigNum &a);
		BigNum& operator += (BigNum &a);

		BigNum operator -(BigNum &a);
		BigNum& operator -= (BigNum &a);

		BigNum operator *(BigNum &a);
		BigNum& operator *= (BigNum &a);

		BigNum operator /(BigNum &a);
		BigNum& operator /= (BigNum &a);

		BigNum operator %(BigNum &a);
		BigNum& operator %= (BigNum &a);

		BigNum& operator ++();
		BigNum& operator --();

		BigNum operator <<(u32 len);
		BigNum operator >>(u32 len);
		BigNum operator &(BigNum &a);
		BigNum operator |(BigNum &a);
		BigNum operator ^(BigNum &a);
		BigNum& operator &=(BigNum &a);
		BigNum& operator |=(BigNum &a);
		BigNum& operator ^=(BigNum &a);

		void from(const unsigned char* a, u32 len);
		u32 to(unsigned char* a, u32 len);

		void setBit(u32 bit, s32 value);
		u32 getNumBits();

		BigNum square();
		BigNum& squareEqu();

		BigNum sqrt();
		BigNum& sqrtEqu();

		/* Compute y = x^e mod m */
		BigNum modExp(BigNum &e, BigNum &m);
		BigNum& modExpEqu(BigNum &e, BigNum &m);

		/* Compute a = (x * y) mod m */
		BigNum modMult(BigNum &a,BigNum &y, BigNum &m);
		BigNum& modMultEqu(BigNum &y, BigNum &m);

		/* Compute x = a^-1 mod m */
		BigNum modInv(BigNum &m);
		BigNum& modInvEqu(BigNum &m);

		/* Compute g = gcd(x, y) */
		BigNum gcd(BigNum &y);
		BigNum& gcdEqu(BigNum &y);

		bool isPrime(u32 tests);
		bool rabinMiller(u32 tests);

		//! Uses the default (not very random or secure) rng unless you pass your own.
		void rand(u32 n_bits, IRng* rng = 0);
		void randPrime(u32 n_bits, u32 tests = 2, IRng* rng = 0);

	protected:

		void* BDNum;
	};

}
}

#endif
