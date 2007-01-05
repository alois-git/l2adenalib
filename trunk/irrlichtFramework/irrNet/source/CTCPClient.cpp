/*
 * CTCPClient.h - TCP Client interface.
 * Created 12/8/2006, by Michael 'Bigcheese' Spencer.
 */

#include <CTCPClient.h>
#include <INetEvent.h>

namespace irr
{
namespace net
{

CTCPClient::CTCPClient(void* eventCallBack)
: IClient(eventCallBack)
{
	EventCallBack = eventCallBack;
	rc = RateController();
	Startup();
};

CTCPClient::~CTCPClient()
{
	::close(Sock);
};

void CTCPClient::run()
{
	c8 buff[SERVER_CLIENT_BUFFER_SIZE];
	while(Running){
		int ret = ::recv(Sock, buff, SERVER_CLIENT_BUFFER_SIZE, NULL);
		if(ret == 0)
		{
			// Client disconnected.
			Running = false;
			disconnect();
			return;
		}else if(ret == -1)
		{
			// Socket error.
			Running = false;
			puts(gai_strerror(WSAGetLastError()));
			disconnect();
			return;
		}else
		{
			// Call event.
			NetEvent ne;
			ne.enet = ENET_RECVDATA;
			ne.client = this;
			ne.recvData.data = buff;
			ne.recvData.dataLen = ret;
			ne.ec = EC_CLIENT;
			((INetEvent*)EventCallBack)->OnEvent(ne);
		}
	}
};

bool CTCPClient::connect(Address &a, s32 af)
{
	if(a.resActive != 0)
	{
		Sock = ::socket(af, SOCK_STREAM, IPPROTO_TCP);
		if(Sock < 0)
			return false;

		if(::connect(Sock, a.resActive->ai_addr, a.resActive->ai_addrlen) < 0)
		{
			::close(Sock);
			Sock = -1;
			return false;
		}
	}else
	{
		for(u32 i = 0; i < a.length(); i++)
		{
			a.setActive(i);
			Sock = ::socket(af, SOCK_STREAM, IPPROTO_TCP);
			if(Sock < 0)
				continue;

			if(::connect(Sock, a.resActive->ai_addr, a.resActive->ai_addrlen) < 0)
			{
				::close(Sock);
				Sock = -1;
				continue;
			}else
			{
				return true;
			}
		}
	}
	return true;
};

void CTCPClient::disconnect()
{
	::close(Sock);
};

void CTCPClient::send(c8* data, u32 len)
{
	int sent = 0;
	int lenleft = len;
	while(sent < len)
	{
		rc.waitForNext(len);
		int ret = ::send(Sock, data, lenleft, 0);
		if(ret <= 0)
		{
			puts(gai_strerror(WSAGetLastError()));
		}
		sent += ret;
		data += sent;
		lenleft = len - sent;
	}
};

void CTCPClient::setMaxUpSpeed(u32 speed)
{
	rc.setUnitsPerSecond(speed);
};

}
}
