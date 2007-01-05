/*
 * INetEvent.h - Networking event.
 * Created 12/8/2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_INETEVENT_H_INCLUDED__
#define __IRR_INETEVENT_H_INCLUDED__

#include <irrTypes.h>
#include <IServer.h>
#include <IServerClient.h>
#include <IClient.h>

namespace irr
{
namespace net
{
	enum E_Net_Event_Type
	{
		ENET_CLIENT_CONNECT = 0,
		ENET_CLIENT_DISCONNECT,
		ENET_RECVDATA
	};

	enum E_Con
	{
		EC_SERVER = 0,
		EC_CLIENT
	};

	enum E_Disconnect_Reason
	{
		EDR_KICK = 0,
		EDR_UNKNOWN
	};

	struct S_Client_Disconnect
	{
		E_Disconnect_Reason edr;
	};

	struct S_Recv_Data
	{
		c8* data;
		u32 dataLen;
	};

	struct NetEvent
	{
		E_Net_Event_Type enet;
		E_Con ec;

		union
		{
			IServerClient* serverClient;
			IClient* client;
		};

		IServer* server;

		union
		{
			S_Client_Disconnect clientDisconnect;
			S_Recv_Data recvData;
		};

	};

	class INetEvent
	{
	public:

		virtual ~INetEvent() {}

		virtual void OnEvent(NetEvent &e) = 0;

	};

}
}

#endif
