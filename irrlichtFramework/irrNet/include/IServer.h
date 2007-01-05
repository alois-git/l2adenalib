/*
 * IServer.h - UDP/TCP Server interface.
 * Created 12/8/2006, by Michael 'Bigcheese' Spencer.
 * 
 * Useage:
 * IServer* s = new CXXXServer(IEventReciever* er);
 * s->bind(Address("127.0.0.1","1337"));
 * s->start();
 */

#ifndef __IRR_ISERVER_H_INCLUDED__
#define __IRR_ISERVER_H_INCLUDED__

#include <CThread.h>
#include <irrAddress.h>
#include <irrNetTypes.h>
#include <irrRateController.h>

namespace irr
{
namespace net
{

	class IServer : public core::threads::Thread
	{
	friend class CTCPServerClient;
	public:

		IServer(void* eventCallBack, u32 backLog)
		: Sock(0), AddressFamily(AF_UNSPEC), BackLog(backLog), EventCallBack(eventCallBack)
		{

		};

		virtual ~IServer() {}

		/*
		 * Threaded sever implementation.
		 *** DONT CALL (Call start()) ***
		 */
		virtual void run() = 0;

		/*
		 * Binds socket to the active address in a. If no address is active binds all adresses in a.
		 * Returns the number of binds that failed.
		 */
		virtual u32 bind(Address &a, s32 af = AF_INET) = 0;

		/*
		 * Sends data to all connected clients exluding thoes in the exclude list.
		 */
		//virtual void broadcast() = 0;

		virtual void kickClient(void* client) = 0;
		// TODO: virtual void banClient(IServerClient* client) = 0;

		/*
		 * Sets the max upload rate for the socket in bytes per second.
		 * Set speed to 0 for no limit.
		 */
		virtual void setMaxUpSpeed(u32 speed) = 0;

		/*
		 * Sets the max upload rate for each in bytes per second.
		 * Set speed to 0 for no limit.
		 * Note: this can be overriden by calling setMaxUpSpeed on a client connection.
		 */
		virtual void setMaxUpSpeedPerClient(u32 speed) = 0;

	protected:

		Socket Sock;
		s32 AddressFamily;
		u32 BackLog;
		void* EventCallBack;

	};

}
}

#endif
