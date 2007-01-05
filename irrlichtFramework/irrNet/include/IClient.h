/*
 * IClient.h - UDP/TCP Client interface.
 * Created 12/8/2006, by Michael 'Bigcheese' Spencer.
 * 
 * Useage:
 * CXXXClient c(EventCallBack);
 * c.connect(Address("google.com", "80"));
 * c.start();
 */

#ifndef __IRR_ICLIENT_H_INCLUDED__
#define __IRR_ICLIENT_H_INCLUDED__

#include <CThread.h>
#include <irrAddress.h>
#include <irrNetTypes.h>
#include <irrRateController.h>

namespace irr
{
namespace net
{

	class IClient : public core::threads::Thread
	{
	friend class CTCPServerClient;
	public:

		IClient(void* eventCallBack)
		: Sock(0), AddressFamily(AF_UNSPEC), EventCallBack(eventCallBack)
		{

		};

		virtual ~IClient() {}

		/*
		 * Threaded sever implementation.
		 *** DONT CALL (Call start()) ***
		 */
		virtual void run() = 0;

		virtual bool connect(Address &a, s32 af = AF_INET) = 0;

		virtual void disconnect() = 0;

		virtual void send(c8* data, u32 len) = 0;

		//virtual s32 recv(c8* data, u32 len) = 0;

		virtual void setMaxUpSpeed(u32 speed) = 0;

	protected:

		Socket Sock;
		s32 AddressFamily;
		void* EventCallBack;

	};

}
}

#endif
