/*
* CTCPServer.h - TCP Server.
* Created 12/8/2006, by Michael 'Bigcheese' Spencer.
*/

#ifndef __IRR_TCPSERVER_H_INCLUDED__
#define __IRR_TCPSERVER_H_INCLUDED__

#include <IServer.h>
#include <IServerClient.h>
#include <CMutex.h>

namespace irr
{
namespace net
{

	class IRRNET_API CTCPServer : public IServer
	{
	public:

		CTCPServer(void* eventCallBack, u32 backLog);

		virtual ~CTCPServer();

		/*
		 * Threaded sever implementation.
		 *** DONT CALL (Call start()) ***
		 */
		virtual void run();

		/*
		 * Binds socket to the active address in a. If no address is active binds all adresses in a.
		 * Returns the number of binds that failed.
		 */
		virtual u32 bind(Address &a, s32 af = AF_INET);

		/*
		 * Sends data to all connected clients exluding thoes in the exclude list.
		 */
		//virtual void broadcast();

		virtual void kickClient(void* client);

		/*
		 * Sets the max upload rate for the socket in bytes per second.
		 * Set speed to 0 for no limit.
		 */
		virtual void setMaxUpSpeed(u32 speed);

		/*
		 * Sets the max upload rate for each in bytes per second.
		 * Set speed to 0 for no limit.
		 * Note: this can be overriden by calling setMaxUpSpeed on a client connection.
		 */
		virtual void setMaxUpSpeedPerClient(u32 speed);

	private:

		void addClient(IServerClient* client);

		core::list<IServerClient*> ClientList;
		core::threads::Mutex ClientListMutex;

	};

}
}

#endif
