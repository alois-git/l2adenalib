/*
 * SKeyPair.h - Key pair.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_S_KEY_PAIR_H_INCLUDED__
#define __IRR_S_KEY_PAIR_H_INCLUDED__

#include <ISerializable.h>
#include <irrByteStream.h>

namespace irr
{
namespace crypt
{

	struct SPvtKey : public ISerializable
	{
		//! Define someplace else.
	};

	struct SPubKey : public ISerializable
	{
		//! Define someplace else.
	};

	struct SKeyPair : public ISerializable
	{
		SPvtKey *pvtkey;
		SPubKey *pubkey;
	};

	struct SRSAPvtKey : public SPvtKey
	{
		ByteStream<> *n;
		ByteStream<> *d;
	};

	struct SRSAPubKey : public SPvtKey
	{
		ByteStream<> *n;
		ByteStream<> *e;
	};


}
}

#endif
