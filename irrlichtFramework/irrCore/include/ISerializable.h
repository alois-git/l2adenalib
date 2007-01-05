/*
 * ISerializable.h - Serializable interface.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_I_SERIALIZABLE_H_INCLUDED__
#define __IRR_I_SERIALIZABLE_H_INCLUDED__

#include <irrByteStream.h>

namespace irr
{

	class ISerializable
	{
	public:

		virtual ~ISerializable() {}

		virtual ByteStream<>* serialize() = 0;

		virtual void deserialize(ByteStream<> &bs) = 0;

	};

}

#endif
