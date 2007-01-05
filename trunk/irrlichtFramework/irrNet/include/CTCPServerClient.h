/*
 * CTCPServerClient.h - TCP Server client.
 * Created 12/8/2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_TCPSERVERCLIENT_H_INCLUDED__
#define __IRR_TCPSERVERCLIENT_H_INCLUDED__

#include <IServerClient.h>

namespace irr
{
namespace net
{

	class CTCPServerClient : public IServerClient
	{
	public:

		CTCPServerClient(Socket sock, IServer* server);

		virtual ~CTCPServerClient();

		/*
		 * Threaded sever implementation.
		 *** DONT CALL (Call start()) ***
		 */
		virtual void run();

		virtual void send(c8* data, u32 len);

		virtual s32 recv(c8* data, u32 len);

	protected:

		Socket Sock;
		s32 AddressFamily;

	};

}
}

#endif
