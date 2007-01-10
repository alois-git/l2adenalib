/*
 * irrNetTypes.h - Types.
 * Created November 4, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_NET_TYPES_H_INCLUDED__
#define __IRR_NET_TYPES_H_INCLUDED__

#include <irrCompileConfig.h>

#ifdef _IRR_WINDOWS_
#ifdef IRRNET_EXPORTS
#define IRRNET_API __declspec(dllexport)
#else
#define IRRNET_API __declspec(dllimport)
#endif // IRRNET_EXPORTS
#else
#define IRRNET_API 
#endif // _IRR_WINDOWS_ 

#ifdef WIN32
  #undef UNICODE
  #include <winsock2.h> // For socket(), connect(), send(), and recv()
  #include <Ws2tcpip.h>

#else
  #include <sys/types.h>       // For data types
  #include <sys/socket.h>      // For socket(), connect(), send(), and recv()
  #include <netdb.h>           // For gethostbyname()
  #include <arpa/inet.h>       // For inet_addr()
  #include <unistd.h>          // For close()
  #include <netinet/in.h>      // For sockaddr_in
#endif

#include <AVL.h>

#define SERVER_CLIENT_BUFFER_SIZE 2048

namespace irr
{
	namespace net
	{
		/*
		 * For Startup and Cleanup.
		 */
		extern int OpenSockets;
		extern WSADATA wsaData;

		/*
		 * On windows checks to see if WSAStartup has been called.
		 */
		bool IRRNET_API Startup();

		/*
		 * On windows calls WSACleanup if valid.
		 */
		bool IRRNET_API Cleanup();

		enum EPROTOCOL
		{
			//! TCP protocol.
			EP_TCP = 0,

			//! UDP protocol.
			EP_UDP,

			//! Custom reliable UDP protocol.
			EP_IRRP
		};

		enum EPACKET_TYPE
		{
			//! Raw user data.
			EPT_USER_DATA = 0,

			//! User defined packet.
			EPT_USER_PACKET,

			//! RPC.
			EPT_RPC
		};

		typedef void* (*irrNetRPC)(void*);

		#ifdef _IRR_WINDOWS_
		typedef SOCKET Socket;
		#define nclose(x) closesocket(x)
		#else
		typedef int Socket;
		#define nclose(x) close(x)
		#endif
	}
}

#endif
