/*
 * irrNet.cpp - irrNet.
 * Created November 3, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <irrNet.h>
#include <irrNetTypes.h>

namespace irr
{
namespace net
{

int OpenSockets = -1; // -1 Means WSAStartup has not been called.
WSADATA wsaData;

bool Startup()
{
	#ifdef _IRR_WINDOWS_
	if(OpenSockets != -1) // If statup has been called before, do nothing.
		return true;

	int error = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if(error)
	{
		return false;
	}
	OpenSockets = 0;
	#endif
	return true;
};

bool Cleanup()
{
	#ifdef _IRR_WINDOWS_
	if(OpenSockets == -1)
		return false;
	if(OpenSockets == 0)
	{
		WSACleanup();
		return true;
	}else
	{
		return false;
	}
	#endif
	return true;
};

}
}
