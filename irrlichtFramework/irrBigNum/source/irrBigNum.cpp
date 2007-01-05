/*
 * irrBigNum.cpp - Large number class.
 * Created November 21, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <irrBigNum.h>
#include "bigd.h"
#include "bigdRand.h"
#include <stdlib.h>
#include <time.h>
#include <CDefaultRNG.h>

namespace irr
{
namespace math
{

BigNum::BigNum(void)
{
	BDNum = (void*)bdNew();
};

BigNum::BigNum(BigNum &a)
{
	BDNum = (void*)bdNew();
	bdSetEqual((BIGD)this->BDNum, (BIGD)a.BDNum);
};

BigNum::BigNum(u32 num)
{
	BDNum = (void*)bdNew();
	bdSetShort((BIGD)this->BDNum, num);
};

BigNum::~BigNum()
{
	bdFree((BIGD*)&BDNum);
};

void BigNum::print()
{
	u32 len = bdConvToDecimal((BIGD)this->BDNum, NULL, NULL);
	char* buffer = new char[len + 1];
	bdConvToDecimal((BIGD)this->BDNum, buffer, len + 1);
	printf("%s", buffer);
	delete[] buffer;
};

BigNum& BigNum::operator =(BigNum &a)
{
	bdSetEqual((BIGD)this->BDNum, (BIGD)a.BDNum);
	return *this;
};

BigNum& BigNum::operator =(u32 num)
{
	bdSetShort((BIGD)this->BDNum, num);
	return *this;
};

bool BigNum::operator ==(BigNum &a)
{
	return bdIsEqual((BIGD)this->BDNum, (BIGD)a.BDNum);
};
bool BigNum::operator !=(BigNum &a)
{
	return !bdIsEqual((BIGD)this->BDNum, (BIGD)a.BDNum);
};

bool BigNum::operator <(BigNum &a)
{
	int ret = bdCompare((BIGD)this->BDNum, (BIGD)a.BDNum);
	if(ret == -1)
		return true;
	return false;
};

bool BigNum::operator >(BigNum &a)
{
	int ret = bdCompare((BIGD)this->BDNum, (BIGD)a.BDNum);
	if(ret == 1)
		return true;
	return false;
};


BigNum BigNum::operator +(BigNum &a)
{
	BigNum ret = BigNum();
	bdAddEx((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return ret;
};

BigNum& BigNum::operator +=(BigNum &a)
{
	bdAddEx((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return *this;
};

BigNum BigNum::operator -(BigNum &a)
{
	BigNum ret = BigNum();
	bdSubtractEx((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return ret;
};

BigNum& BigNum::operator -=(BigNum &a)
{
	bdSubtractEx((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return *this;
};

BigNum BigNum::operator *(BigNum &a)
{
	BigNum ret = BigNum();
	bdMultiplyEx((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return ret;
};

BigNum& BigNum::operator *=(BigNum &a)
{
	bdMultiplyEx((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return *this;
};

BigNum BigNum::operator /(BigNum &a)
{
	BigNum ret = BigNum();
	BigNum r = BigNum();
	bdDivideEx((BIGD)ret.BDNum, (BIGD)r.BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return ret;
};

BigNum& BigNum::operator /=(BigNum &a)
{
	BigNum r = BigNum();
	bdDivideEx((BIGD)this->BDNum, (BIGD)r.BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return *this;
};

BigNum BigNum::operator %(BigNum &a)
{
	BigNum ret = BigNum();
	bdModuloEx((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return ret;
};

BigNum& BigNum::operator %=(BigNum &a)
{
	bdModuloEx((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return *this;
};

BigNum& BigNum::operator ++()
{
	bdIncrement((BIGD)this->BDNum);
	return *this;
};

BigNum& BigNum::operator --()
{
	bdDecrement((BIGD)this->BDNum);
	return *this;
};

BigNum BigNum::operator <<(u32 len)
{
	BigNum ret = BigNum();
	bdShiftLeft((BIGD)ret.BDNum, (BIGD)this->BDNum, len);
	return ret;
};

BigNum BigNum::operator >>(u32 len)
{
	BigNum ret = BigNum();
	bdShiftRight((BIGD)ret.BDNum, (BIGD)this->BDNum, len);
	return ret;
};

BigNum BigNum::operator &(BigNum &a)
{
	BigNum ret = BigNum();
	bdAndBits((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return ret;
};

BigNum BigNum::operator |(BigNum &a)
{
	BigNum ret = BigNum();
	bdOrBits((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return ret;
};

BigNum BigNum::operator ^(BigNum &a)
{
	BigNum ret = BigNum();
	bdXorBits((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return ret;
};

BigNum& BigNum::operator &=(BigNum &a)
{
	bdAndBits((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return *this;
};

BigNum& BigNum::operator |=(BigNum &a)
{
	bdOrBits((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return *this;
};

BigNum& BigNum::operator ^=(BigNum &a)
{
	bdXorBits((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)a.BDNum);
	return *this;
};

void BigNum::from(const unsigned char *a, u32 len)
{
	bdConvFromOctets((BIGD)this->BDNum, a, len);
};

u32 BigNum::to(unsigned char *a, u32 len)
{
	return bdConvToOctets((BIGD)this->BDNum, a, len);
};

void BigNum::setBit(u32 bit, s32 value)
{
	bdSetBit((BIGD)this->BDNum, bit, value);
};

u32 BigNum::getNumBits()
{
	return bdBitLength((BIGD)this->BDNum);
};

BigNum BigNum::square()
{
	BigNum ret = BigNum();
	bdSquareEx((BIGD)ret.BDNum, (BIGD)this->BDNum);
	return ret;
};

BigNum& BigNum::squareEqu()
{
	bdSquareEx((BIGD)this->BDNum, (BIGD)this->BDNum);
	return *this;
};

BigNum BigNum::sqrt()
{
	BigNum ret = BigNum();
	bdSqrt((BIGD)ret.BDNum, (BIGD)this->BDNum);
	return ret;
};

BigNum& BigNum::sqrtEqu()
{
	bdSqrt((BIGD)this->BDNum, (BIGD)this->BDNum);
	return *this;
};

BigNum BigNum::modExp(BigNum &e, BigNum &m)
{
	BigNum ret = BigNum();
	bdModExp((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)e.BDNum, (BIGD)m.BDNum);
	return ret;
};

BigNum& BigNum::modExpEqu(BigNum &e, BigNum &m)
{
	bdModExp((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)e.BDNum, (BIGD)m.BDNum);
	return *this;
};

BigNum BigNum::modMult(BigNum &a, BigNum &y, BigNum &m)
{
	BigNum ret = BigNum();
	bdModMult((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)y.BDNum, (BIGD)m.BDNum);
	return ret;
};

BigNum& BigNum::modMultEqu(BigNum &y, BigNum &m)
{
	bdModMult((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)y.BDNum, (BIGD)m.BDNum);
	return *this;
};

BigNum BigNum::modInv(BigNum &m)
{
	BigNum ret = BigNum();
	bdModInv((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)m.BDNum);
	return ret;
};

BigNum& BigNum::modInvEqu(BigNum &m)
{
	bdModInv((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)m.BDNum);
	return *this;
};

BigNum BigNum::gcd(BigNum &y)
{
	BigNum ret = BigNum();
	bdGcd((BIGD)ret.BDNum, (BIGD)this->BDNum, (BIGD)y.BDNum);
	return ret;
};

BigNum& BigNum::gcdEqu(BigNum &y)
{
	bdGcd((BIGD)this->BDNum, (BIGD)this->BDNum, (BIGD)y.BDNum);
	return *this;
};

bool BigNum::isPrime(u32 tests)
{
	return bdIsPrime((BIGD)this->BDNum, tests);
};

bool BigNum::rabinMiller(u32 tests)
{
	return bdRabinMiller((BIGD)this->BDNum, tests);
};

int rand_Func(unsigned char *buf, size_t nbytes, const unsigned char *seed, size_t seedlen)
{
	bool pvtseed = false;
	if(seed == NULL)
	{
		seed = (const unsigned char*)new CDefaultRNG();
		pvtseed = true;
	}
	((IRng*)seed)->getRandBuffer((c8*)buf, nbytes);
	if(pvtseed)
		delete seed;
	return nbytes;
};

void BigNum::rand(u32 n_bits, IRng* rng)
{
	// rng is passed like this so i have access to it in rand_Func.
	bdRandomSeeded((BIGD)this->BDNum, n_bits, (const unsigned char*) rng, 4, rand_Func);
};

void BigNum::randPrime(u32 n_bits, u32 tests, IRng* rng)
{
	// rng is passed like this so i have access to it in rand_Func.
	bdGeneratePrime((BIGD)this->BDNum, n_bits, tests, (const unsigned char*) rng, 4, rand_Func);
};

}
}
