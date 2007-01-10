/*
 * BDRSA.cpp - This is the BigDidgets RSA keygen/cipher modified into a c++ class.
 * Created Arpil 21, 2006, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Michael Spencer - bigcheesegs@gmail.com
 */

#include "BDRSA.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <memory.h>
#include "bigd.h"

static int my_rand(unsigned char *bytes, size_t nbytes, unsigned char *seed, size_t seedlen)
/* Our own (very insecure) random generator func using good old rand() 
   but in the required format for BD_RANDFUNC
   -- replace this in practice with your own cryptographically-secure function.
*/
{
	unsigned int myseed;
	size_t i;
	int offset;

	/* Use time for 32-bit seed - then blend in user-supplied seed, if any */
	myseed = (unsigned)time(NULL);
	if (seed)
	{
		for (offset = 0, i = 0; i < seedlen; i++, offset = (offset + 1) % sizeof(unsigned))
			myseed ^= ((unsigned int)seed[i] << (offset * 8));
	}

	srand(myseed);
	while (nbytes--)
	{
		*bytes++ = rand() & 0xFF;
	}

	return 0;
}

static bdigit_t SMALL_PRIMES[] = {
	3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 
	47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 
	103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
	233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
	353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
	419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
	467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
	547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
	607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
	661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
	739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
	811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
	877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
	947, 953, 967, 971, 977, 983, 991, 997,
};
#define N_SMALL_PRIMES (sizeof(SMALL_PRIMES)/sizeof(bdigit_t))

int generateRSAPrime(BIGD p, size_t nbits, bdigit_t e, size_t ntests, 
				 unsigned char *seed, size_t seedlen, BD_RANDFUNC randFunc)
/* Create a prime p such that gcd(p-1, e) = 1.
   Returns # prime tests carried out or -1 if failed.
   Sets the TWO highest bits to ensure that the 
   product pq will always have its high bit set.
   e MUST be a prime > 2.
   This function assumes that e is prime so we can
   do the less expensive test p mod e != 1 instead
   of gcd(p-1, e) == 1.
   Uses improvement in trial division from Menezes 4.51.
  */
{
	BIGD u;
	size_t i, j, iloop, maxloops, maxodd;
	int done, overflow, failedtrial;
	int count = 0;
	bdigit_t r[N_SMALL_PRIMES];

	/* Create a temp */
	u = bdNew();

	maxodd = nbits * 100;
	maxloops = 5;

	done = 0;
	for (iloop = 0; !done && iloop < maxloops; iloop++)
	{
		/* Set candidate n0 as random odd number */
		bdRandomSeeded(p, nbits, seed, seedlen, randFunc);
		/* Set two highest and low bits */
		bdSetBit(p, nbits - 1, 1);
		bdSetBit(p, nbits - 2, 1);
		bdSetBit(p, 0, 1);

		/* To improve trial division, compute table R[q] = n0 mod q
		   for each odd prime q <= B
		*/
		for (i = 0; i < N_SMALL_PRIMES; i++)
		{
			r[i] = bdShortMod(u, p, SMALL_PRIMES[i]);
		}

		done = overflow = 0;
		/* Try every odd number n0, n0+2, n0+4,... until we succeed */
		for (j = 0; j < maxodd; j++, overflow = bdShortAdd(p, p, 2))
		{
			/* Check for overflow */
			if (overflow)
				break;

			count++;

			/* Each time 2 is added to the current candidate
			   update table R[q] = (R[q] + 2) mod q */
			if (j > 0)
			{
				for (i = 0; i < N_SMALL_PRIMES; i++)
				{
					r[i] = (r[i] + 2) % SMALL_PRIMES[i];
				}
			}

			/* Candidate passes the trial division stage if and only if
			   NONE of the R[q] values equal zero */
			for (failedtrial = 0, i = 0; i < N_SMALL_PRIMES; i++)
			{
				if (r[i] == 0)
				{
					failedtrial = 1;
					break;
				}
			}
			if (failedtrial)
				continue;

			/* If p mod e = 1 then gcd(p, e) > 1, so try again */
			bdShortMod(u, p, e);
			if (bdShortCmp(u, 1) == 0)
				continue;

			/* Do expensive primality test */
			if (bdRabinMiller(p, ntests))
			{	/* Success! - we have a prime */
				done = 1;
				break;
			}

		}
	}
	

	/* Clear up */
	bdFree(&u);

	return (done ? count : -1);
}

int generateRSAKey(BIGD n, BIGD e, BIGD d, BIGD p, BIGD q, size_t nbits, bdigit_t ee, size_t ntests, unsigned char *seed, size_t seedlen, 
	BD_RANDFUNC randFunc)
{
	BIGD g, p1, q1, phi;
	size_t np, nq;
	unsigned char *myseed = NULL;
	int res;

	/* Initialise */
	g = bdNew();
	p1 = bdNew();
	q1 = bdNew();
	phi = bdNew();
	
	/* We add an extra byte to the user-supplied seed */
	myseed = (unsigned char*)malloc(seedlen + 1);
	if (!myseed) return -1;
	memcpy(myseed, seed, seedlen);

	/* Do (p, q) in two halves, approx equal */
	nq = nbits / 2 ;
	np = nbits - nq;

	/* Make sure seeds are slightly different for p and q */
	bdSetShort(e, ee);
reprime:
	myseed[seedlen] = 0x03;
	res = generateRSAPrime(p, np, ee, ntests, myseed, seedlen+1, randFunc);
	assert(res > 0);
	myseed[seedlen] = 0xef;
	res = generateRSAPrime(q, nq, ee, ntests, myseed, seedlen+1, randFunc);
	assert(res > 0);

	/* Check that p != q (if so, RNG is faulty!) */
	assert(!bdIsEqual(p, q));

	/* If q > p swap p and q so p > q */
	if (bdCompare(p, q) < 1)
	{	
		bdSetEqual(g, p);
		bdSetEqual(p, q);
		bdSetEqual(q, g);
	}

	/* Calc p-1 and q-1 */
	bdSetEqual(p1, p);
	bdDecrement(p1);
	bdSetEqual(q1, q);
	bdDecrement(q1);

	/* Check gcd(p-1, e) = 1 */
	//bdGcd(g, p1, e);
	//assert(bdShortCmp(g, 1) == 0);
	//bdGcd(g, q1, e);
	//assert(bdShortCmp(g, 1) == 0);

	/* Compute n = pq */
	bdMultiply(n, p, q);

	/* Compute d = e^-1 mod (p-1)(q-1) */
	bdMultiply(phi, p1, q1);
	res = bdModInv(d, e, phi);
	if(res != 0)
		goto reprime;

	/* Check ed = 1 mod phi */
	bdModMult(g, e, d, phi);

	/* Clean up */
	if (myseed) free(myseed);
	bdFree(&g);
	bdFree(&p1);
	bdFree(&q1);
	bdFree(&phi);

	return 0;
}

BDRSA::BDRSA(int bits, unsigned long ee){
	// Class vars
	n = bdNew();
	d = bdNew();
	e = bdNew();
	// PVT vars (cleaned after startup)
	BIGD p, q;
	p = bdNew();
	q = bdNew();
	unsigned char *seed = NULL;
	size_t seedlen = 0;

	generateRSAKey(n, e, d, p, q, bits, ee, 100, seed, seedlen, (BD_RANDFUNC)my_rand);

	bdFree(&p);
	bdFree(&q);
};

BDRSA::~BDRSA(){
	bdFree(&n);
	bdFree(&d);
};

void BDRSA::getMod(char* buff, int len){
	// Get the size of the str we need.
	bdConvToOctets(n, (unsigned char*)buff, len);
};

void BDRSA::encrypt(char* in, int in_len, char* out, int out_len){
	BIGD m = bdNew();
	bdConvFromOctets(m, (unsigned char*)in, in_len);
	BIGD c = bdNew();
	bdModExp(c, m, e, n);
	bdConvToOctets(c, (unsigned char*)out, out_len);
};

void BDRSA::decrypt(char* in, int in_len, char* out, int out_len){
	BIGD m = bdNew();
	bdConvFromOctets(m, (const unsigned char*)in, in_len);
	BIGD c = bdNew();
	bdModExp(c, m, d, n);
	bdConvToOctets(c, (unsigned char*)out, out_len);
};
