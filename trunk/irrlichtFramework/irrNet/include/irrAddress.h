/*
 * irrAddress.h - ipv4/ipv6 internet address.
 * Created November 4, 2006, by Michael 'Bigcheese' Spencer.
 *
 * Useage:
 * Create a new address
 * Adress(stringc addr, stringc port);
 * addr: Ipv4, Ipv6 or a domain name (ex: 127.0.0.1, ::1, google.com).
 * port: a numeric port or service name (ex: http, 7777, 1337).
 *
 * Select ip (because a domain name can map to more than 1 ip)
 * Use the u32 length() member function to get how many ip/ports there are.
 * Use the [] operator to return a struct with 2 strings, ip and port.
 * Use the void setActive(u32) member function to set witch one to use.
  if not called defaults to the first entry.
 */

#ifndef __IRR_ADDRESS_H_INCLUDED__
#define __IRR_ADDRESS_H_INCLUDED__

#include <irrString.h>
#include <irrTypes.h>
#include <irrNetTypes.h>

namespace irr
{
namespace net
{
	struct ipport
	{
		core::stringc addr;
		core::stringc port;
	};

	class IRRNET_API Address
	{
	public:

		Address();
		Address(core::stringc addr, core::stringc port);

		~Address();

		// Returns a struct with the ip and port as stringc.
		ipport operator [](u32 index);

		// Returns the number of ip/port pairs.
		u32 length();

		// Sets which ip/port pair to use.
		void setActive(u32 index);

		addrinfo *resRoot;
		addrinfo *resActive;

	private:
	};

}
}

#endif
