/*
 * IKey.h - key.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_KEY_H_INCLUDED__
#define __IRR_KEY_H_INCLUDED__

#include <ISerializable.h>

namespace irr
{
namespace crypt
{

	class IKey : public ISerializable
	{
	public:

		virtual ~IKey() {}

	};
}
}

#endif
