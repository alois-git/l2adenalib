/*
 * irrAddress.cpp - ipv4/ipv6 internet address.
 * Created November 4, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <irrAddress.h>
#include <irrNetTypes.h>

namespace irr
{
namespace net
{

Address::Address()
: resRoot(0), resActive(0)
{

};

Address::Address(core::stringc addr, core::stringc port)
: resRoot(0), resActive(0)
{
	Startup();
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_protocol = SOCK_STREAM;
	int error = 0;
	error = getaddrinfo(addr.c_str(), port.c_str() , &hints, &resRoot);
	if(error)
	{
		printf("getaddrinfo failed... %s %s %s\n", addr.c_str(), port.c_str(), gai_strerror(error));
		freeaddrinfo(resRoot);
		resRoot = resActive = 0;
		return;
	}
};

Address::~Address()
{
	if(resRoot)
		freeaddrinfo(resRoot);
};

ipport Address::operator [](u32 index)
{
	ipport ret;
	if(resRoot == 0)
		return ret;
	addrinfo *res = resRoot;
	u32 i;
	for (i = 0; i < index; i++)
	{
		if(res->ai_next != NULL)
			res = res->ai_next;
		else
			break;
	}
	char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
	int error = getnameinfo(res->ai_addr, res->ai_addrlen, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
	if(error)
	{
		fprintf(stderr, "%s\n", gai_strerror(error));
	}
	ret.addr = core::stringc(hbuf);
	ret.port = core::stringc(sbuf);
	return ret;
};

u32 Address::length()
{
	if(resRoot == 0)
		return 0;
	addrinfo *res = resRoot;
	u32 i;
	for (i = 1; ; i++)
	{
		if(res->ai_next != NULL)
			res = res->ai_next;
		else
			break;
	}
	return i;
};

void Address::setActive(u32 index)
{
	if(resRoot == 0)
		return;
	addrinfo *res = resRoot;
	u32 i;
	for (i = 0; i < index; i++)
	{
		if(res->ai_next != NULL)
			res = res->ai_next;
		else
			break;
	}
	resActive = res;
};

}
}
