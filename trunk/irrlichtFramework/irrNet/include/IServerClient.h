/*
 * IServerClient.h - UDP/TCP Server client interface.
 * Created 12/8/2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_ISERVERCLIENT_H_INCLUDED__
#define __IRR_ISERVERCLIENT_H_INCLUDED__

#include <CThread.h>
#include <irrAddress.h>
#include <irrNetTypes.h>
#include <IServer.h>

namespace irr
{
namespace net
{

	class IServerClient : public core::threads::Thread
	{
	friend class CTCPServer;
	public:

		IServerClient(Socket sock, IServer* server)
		: Sock(sock), AddressFamily(AF_UNSPEC), Server(server)
		{

		};

		virtual ~IServerClient() {}

		/*
		 * Threaded sever implementation.
		 *** DONT CALL (Call start()) ***
		 */
		virtual void run() = 0;

		virtual void send(c8* data, u32 len) = 0;

		virtual s32 recv(c8* data, u32 len) = 0;

		void* UserData;

	protected:

		Socket Sock;
		s32 AddressFamily;
		IServer* Server;
		RateController rc;

	};

}
}

#endif
