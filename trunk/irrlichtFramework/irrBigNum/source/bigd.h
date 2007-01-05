/* $Id: bigd.h $ */

/******************** SHORT COPYRIGHT NOTICE**************************
This source code is part of the BigDigits multiple-precision
arithmetic library Version 2.1 originally written by David Ireland,
copyright (c) 2001-6 D.I. Management Services Pty Limited, all rights
reserved. It is provided "as is" with no warranties. You may use
this software under the terms of the full copyright notice
"bigdigitsCopyright.txt" that should have been included with this
library or can be obtained from <www.di-mgt.com.au/bigdigits.html>.
This notice must always be retained in any copy.
******************* END OF COPYRIGHT NOTICE***************************/
/*
	Last updated:
	$Date: 2006-08-23 11:13:00 $
	$Revision: 2.1.0 $
	$Author: dai $
*/

/* 
Interface to the BIGD library (BigDigits "bd" functions)
Multiple-precision arithmetic for non-negative numbers
using memory management and opaque pointers. 
*/

#ifndef BIGD_H_
#define BIGD_H_ 1

#include <irrBigNumCompileConfig.h>

#include <stddef.h>

/**** USER CONFIGURABLE SECTION ****/

/* [v2.1] Changed to use exact width integer types.
   CAUTION: change this, change bigdigits.h to match.
*/
#ifndef HAVE_C99INCLUDES
	#if (__STDC_VERSION >= 199901L) || defined(linux) || defined(__linux__)
	#define HAVE_C99INCLUDES
	#endif
#endif
#ifndef HAVE_SYS_TYPES
	#if defined(unix) || defined(__unix__)
	#define HAVE_SYS_TYPES
	#endif
#endif
#ifdef HAVE_C99INCLUDES
	#include <stdint.h>
#elif defined(HAVE_SYS_TYPES)
	#include <sys/types.h>
#else 
	#define uint32_t unsigned long 
	#define uint16_t unsigned short 
#endif

/* DIGIT_T type is not exposed by this library so we expose 
   a synonym `bdigit_t' for a single digit */
typedef uint32_t bdigit_t;

/* Macros for format specifiers 
-- change these to "u", "x" and "X" if necessary */
#ifdef HAVE_C99INCLUDES
	#include <inttypes.h>
#else 
	#define PRIu32 "lu" 
	#define PRIx32 "lx" 
	#define PRIX32 "lX" 
#endif
/* We define our own based on the C99 standard ones */
#define PRIuBIGD PRIu32
#define PRIxBIGD PRIx32
#define PRIXBIGD PRIX32

/**** END OF USER CONFIGURABLE SECTION ****/

#define OCTETS_PER_DIGIT (sizeof(bdigit_t))
/* Options for bdPrint */
#define BD_PRINT_NL   0x1	/* append a newline after printing */
#define BD_PRINT_TRIM 0x2	/* trim leading zero digits */

/*
This interface uses opaque pointers of type BIGD using
the conventions in "C Interfaces and Implementions" by
David R. Hanson, Addison-Wesley, 1996, pp21-4.
Thanks to Ian Tree for the C++ fudge.
*/
#define T BIGD
#ifdef __cplusplus
	typedef struct T2 *T;
#else
	typedef struct T *T;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* PROGRAMMER'S NOTES
Where the function computes a new BIGD value,
the result is returned in the first argument.
Some functions do not allow variables to overlap (noted by w#v).
Functions of type int generally return 0 to denote success 
but some return True/False (1/0) or borrow (+1) or error (-1).
Functions of type size_t (an unsigned int) return a length.

Memory is allocated if the function might need it. 
It is only released when freed with bdFree(), e.g.:

	BIGD b;
	b = bdNew();
	...
	bdFree(&b);
*/

/******************************/
/* CONSTRUCTOR AND DESTRUCTOR */
/******************************/

BIGD IRRBIGNUM_API bdNew(void);
	/* Return handle to new BIGD object */

void IRRBIGNUM_API bdFree(BIGD *bd);	
	/* Zeroise and free BIGD memory
	   - NB pass a pointer to the handle */

/*************************/
/* ARITHMETIC OPERATIONS */
/*************************/

int IRRBIGNUM_API bdAdd(BIGD w, BIGD u, BIGD v);
	/* Compute w = u + v, w#v */

int IRRBIGNUM_API bdSubtract(BIGD w, BIGD u, BIGD v);
	/* Compute w = u - v, return borrow, w#v */

int IRRBIGNUM_API bdMultiply(BIGD w, BIGD u, BIGD v);
	/* Compute w = u * v, w#u */

int IRRBIGNUM_API bdDivide(BIGD q, BIGD r, BIGD u, BIGD v);
	/* Computes quotient q = u / v and remainder r = u mod v 
	   Trashes q and r first. q#(u,v), r#(u,v) */

int IRRBIGNUM_API bdModulo(BIGD r, BIGD u, BIGD v);
	/* Computes r = u mod v, r#u */

int IRRBIGNUM_API bdSquare(BIGD w, BIGD x);
	/* Computes w = x^2, w#x */

int IRRBIGNUM_API bdIncrement(BIGD a);
	/* Sets a = a + 1, returns carry */

int IRRBIGNUM_API bdDecrement(BIGD a);
	/* Sets a = a - 1, returns borrow */

/* 'Safe' versions with no restrictions on overlap */
int IRRBIGNUM_API bdAddEx(BIGD w, BIGD u, BIGD v);
int IRRBIGNUM_API bdSubtractEx(BIGD w, BIGD u, BIGD v);
int IRRBIGNUM_API bdMultiplyEx(BIGD w, BIGD u, BIGD v);
int IRRBIGNUM_API bdDivideEx(BIGD q, BIGD r, BIGD u, BIGD v);
int IRRBIGNUM_API bdModuloEx(BIGD r, BIGD u, BIGD v);
int IRRBIGNUM_API bdSquareEx(BIGD w, BIGD x);

/* [v2.1.0] new function */
int IRRBIGNUM_API bdSqrt(BIGD s, BIGD x);
	/* Computes integer square root s = floor(sqrt(x)) */

/*************************/
/* COMPARISON OPERATIONS */
/*************************/

int IRRBIGNUM_API bdIsEqual(BIGD a, BIGD b);
	/* Returns true if a == b, else false */

int IRRBIGNUM_API bdCompare(BIGD a, BIGD b);
	/* Returns sign of (a-b) */

int IRRBIGNUM_API bdIsZero(BIGD a);
	/* Returns true if a == 0, else false */

int IRRBIGNUM_API bdIsEven(BIGD a);
int IRRBIGNUM_API bdIsOdd(BIGD a);
	/* Return TRUE or FALSE */

/*************************/
/* ASSIGNMENT OPERATIONS */
/*************************/

int IRRBIGNUM_API bdSetEqual(BIGD a, BIGD b);
	/* Sets a = b */

int IRRBIGNUM_API bdSetZero(BIGD a);
	/* Sets a = 0 */

/****************************/
/* NUMBER THEORY OPERATIONS */
/****************************/

int IRRBIGNUM_API bdModExp(BIGD y, BIGD x, BIGD e, BIGD m);
	/* Compute y = x^e mod m */

int IRRBIGNUM_API bdModMult(BIGD a, BIGD x, BIGD y, BIGD m);
	/* Compute a = (x * y) mod m */

int IRRBIGNUM_API bdModInv(BIGD x, BIGD a, BIGD m);
	/* Compute x = a^-1 mod m */

int IRRBIGNUM_API bdGcd(BIGD g, BIGD x, BIGD y);
	/* Compute g = gcd(x, y) */

int IRRBIGNUM_API bdIsPrime(BIGD b, size_t ntests);
	/* Returns true if passes ntests x Miller-Rabin tests with trial division */

int IRRBIGNUM_API bdRabinMiller(BIGD b, size_t ntests);
	/* Returns true if passes ntests x Miller-Rabin tests without trial division, b > 2 */

/**********************************************/
/* FUNCTIONS THAT OPERATE WITH A SINGLE DIGIT */
/**********************************************/

int IRRBIGNUM_API bdSetShort(BIGD b, bdigit_t d);
	/* Converts single digit d into a BIGD b */

int IRRBIGNUM_API bdShortAdd(BIGD w, BIGD u, bdigit_t d);
	/* Compute w = u + d */

int IRRBIGNUM_API bdShortSub(BIGD w, BIGD u, bdigit_t d);
	/* Compute w = u - d, return borrow */

int IRRBIGNUM_API bdShortMult(BIGD w, BIGD u, bdigit_t d);
	/* Compute w = u * d */

int IRRBIGNUM_API bdShortDiv(BIGD q, BIGD r, BIGD u, bdigit_t d);
	/* Computes quotient q = u / d and remainder r = u mod d */

bdigit_t IRRBIGNUM_API bdShortMod(BIGD r, BIGD u, bdigit_t d);
	/* Computes r = u mod d. Returns r. */

int IRRBIGNUM_API bdShortCmp(BIGD a, bdigit_t d);
	/* Returns sign of (a-d) */

/***********************/
/* BIT-WISE OPERATIONS */
/***********************/

size_t IRRBIGNUM_API bdBitLength(BIGD bd);
	/* Returns number of significant bits in bd */

int IRRBIGNUM_API bdSetBit(BIGD a, size_t n, int value);
	/* Set bit n (0..nbits-1) with value 1 or 0 */

int IRRBIGNUM_API bdGetBit(BIGD a, size_t ibit);
	/* Returns value 1 or 0 of bit n (0..nbits-1) */

/* [v2.1.0] Removed restriction on shift size */
void IRRBIGNUM_API bdShiftLeft(BIGD a, BIGD b, size_t n);
	/* Computes a = b << n */

void IRRBIGNUM_API bdShiftRight(BIGD a, BIGD b, size_t n);
	/* Computes a = b >> n */

/* [v2.1.0] Added ModPowerOf2, Xor, Or and And functions */
void IRRBIGNUM_API bdModPowerOf2(BIGD a, size_t L);
	/* Computes a = a mod 2^L */

void IRRBIGNUM_API bdXorBits(BIGD a, BIGD b, BIGD c);
	/* Computes bitwise operation a = b XOR c */

void IRRBIGNUM_API bdOrBits(BIGD a, BIGD b, BIGD c);
	/* Computes bitwise operation a = b OR c */

void IRRBIGNUM_API bdAndBits(BIGD a, BIGD b, BIGD c);
	/* Computes bitwise operation a = b AND c */

/*******************/
/* MISC OPERATIONS */
/*******************/

size_t IRRBIGNUM_API bdSizeof(BIGD b);
	/* Returns number of significant digits in b */

void IRRBIGNUM_API bdPrint(BIGD bd, size_t flags);
	/* Print bd to stdout (see flags above) */

/***************/
/* CONVERSIONS */
/***************/
/* [v2.1] Tightened up specs here */

/* All bdConv functions return 0 on error */

/* `Octet' = an 8-bit byte */

size_t IRRBIGNUM_API bdConvFromOctets(BIGD b, const unsigned char *octets, size_t nbytes);
	/* Converts nbytes octets into big digit b, resizing b if necessary.
	   Returns actual number of digits set, which may be larger than mpSizeof(b). */

size_t IRRBIGNUM_API bdConvToOctets(BIGD b, unsigned char *octets, size_t nbytes);
	/* Convert big digit b into array of octets, in big-endian order,
	   padding on the left with zeroes to nbytes, or truncating as necessary.
       It returns the exact number of significant bytes <nsig> in the result.
	   If octets is NULL or nbytes == 0 then just return required <nsig>;
       if nbytes== nsig, octets <-    nnnnnn;
       if nbytes > nsig, octets <- 000nnnnnn;
       if nbytes < nsig, octets <-       nnn. */

/* For Hex and Decimal conversions:
   The parameter `smax' in the bdConvFrom functions
   is the size INCLUDING the terminating zero (as in sizeof(s))
   but the bdConvTo functions return the number of characters required
   EXCLUDING the terminating zero.

   The bdConvToHex and bdConvToDecimal functions return the 
   total length of the string they tried to create even if 
   the output string was truncated at a shorter length.
*/

size_t IRRBIGNUM_API bdConvFromHex(BIGD b, const char *s);
	/* Convert string s of hex chars into big digit b. 
	   Returns number of significant digits actually set, which could be 0. */

size_t IRRBIGNUM_API bdConvToHex(BIGD b, char *s, size_t smax);
	/* Convert big digit b into string s of hex characters
	   where s has size smax including the terminating zero.
	   Returns number of chars required for s excluding leading zeroes. 
	   If s is NULL or smax == 0 then just return required size. */

size_t IRRBIGNUM_API bdConvFromDecimal(BIGD b, const char *s);
	/* Convert string s of decimal chars into big digit b. 
	   Returns number of significant digits actually set, which could be 0. */

size_t IRRBIGNUM_API bdConvToDecimal(BIGD b, char *s, size_t smax);
	/* Convert big digit b into string s of decimal characters
	   where s has size smax including the terminating zero.
	   Returns number of chars required for s excluding leading zeroes. 
	   If s is NULL or smax == 0 then just return required size. */


/****************************/
/* RANDOM NUMBER OPERATIONS */
/****************************/

/* [Version 2.1: bdRandDigit and bdRandomBits moved to bigdRand.h] */

size_t IRRBIGNUM_API bdSetRandTest(BIGD a, size_t ndigits);
	/* Fill a with [1,ndigits] pseudo-random digits. Returns # digits set.
	   Randomly clears a random number of bits in the most significant digit.
	   For testing only. Not thread safe. */

/* TYPEDEF for user-defined random byte generator function */
typedef int (* BD_RANDFUNC)(unsigned char *buf, size_t nbytes, const unsigned char *seed, size_t seedlen);

int IRRBIGNUM_API bdRandomSeeded(BIGD a, size_t nbits, const unsigned char *seed, 
	size_t seedlen, BD_RANDFUNC RandFunc);
	/* Generate a random number nbits long using RandFunc */

int IRRBIGNUM_API bdGeneratePrime(BIGD b, size_t nbits, size_t ntests, const unsigned char *seed, 
	size_t seedlen, BD_RANDFUNC RandFunc);
	/* Generate a prime number nbits long; carry out ntests x primality tests */


/****************/
/* VERSION INFO */
/****************/
/* [v2.0.2] added bdVersion */

int IRRBIGNUM_API bdVersion(void);
	/* Returns version number = major*1000+minor*100+release*10+uses_asm(0|1) */


#undef T /* (for opaque BIGD pointer) */

#ifdef __cplusplus
}
#endif

#endif /* BIGD_H_ */
