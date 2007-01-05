/*
 * CTCPClient.h - TCP Client interface.
 * Created 12/8/2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_CTCPCLIENT_H_INCLUDED__
#define __IRR_CTCPCLIENT_H_INCLUDED__

#include <IClient.h>

namespace irr
{
namespace net
{

	class IRRNET_API CTCPClient : public IClient
	{
	friend class CTCPServerClient;
	public:

		CTCPClient(void* eventCallBack);

		virtual ~CTCPClient();

		/*
		 * Threaded sever implementation.
		 *** DONT CALL (Call start()) ***
		 */
		virtual void run();

		virtual bool connect(Address &a, s32 af = AF_INET);

		virtual void disconnect();

		virtual void send(c8* data, u32 len);

		virtual void setMaxUpSpeed(u32 speed);

	protected:

		Socket Sock;
		s32 AddressFamily;
		void* EventCallBack;
		RateController rc;

	};

}
}

#endif
