/*
* CTCPServer.h - TCP Server.
* Created 12/8/2006, by Michael 'Bigcheese' Spencer.
*/

#include <CTCPServerClient.h>
#include <INetEvent.h>

namespace irr
{
namespace net
{

CTCPServerClient::CTCPServerClient(Socket sock, IServer *server)
: IServerClient(sock, server)
{
	Sock = sock;
	Server = server;
	rc = RateController();
};

CTCPServerClient::~CTCPServerClient()
{

};

void CTCPServerClient::run()
{
	c8 buff[ 1 /*SERVER_CLIENT_BUFFER_SIZE*/];
	while(Running){
		int ret = ::recv(Sock, buff, 1, MSG_PEEK); // See if there is any data.
		if(Sock == 0)
		{
			delete this;
			return;
		}
		if(ret == 0)
		{
			// Client disconnected.
			Running = false;
			if(Running)
				Server->kickClient(this);
			return;
		}else if(ret == -1)
		{
			// Socket error.
			Running = false;
			puts(gai_strerror(WSAGetLastError()));
			if(Server->Running)
				Server->kickClient(this);
			return;
		}else
		{
			// Call event.
			NetEvent ne;
			ne.serverClient = this;
			ne.server = Server;
			ne.enet = ENET_RECVDATA;
			ne.ec = EC_SERVER;
			((INetEvent*)Server->EventCallBack)->OnEvent(ne);
		}
	}
};

void CTCPServerClient::send(c8* data, u32 len)
{
	u32 sent = 0;
	u32 lenleft = len;
	while(sent < len)
	{
		rc.waitForNext(len);
		sent += ::send(Sock, data, lenleft, 0);
		data += sent;
		lenleft = len - sent;
	}
};

s32 CTCPServerClient::recv(c8* data, u32 len)
{
	int ret = ::recv(Sock, data, len, NULL);
	if(ret == 0)
	{
		// Client disconnected.
		Running = false;
		if(Running)
			Server->kickClient(this);
		return 0;
	}else if(ret == -1)
	{
		// Socket error.
		Running = false;
		puts(gai_strerror(WSAGetLastError()));
		if(Running)
			Server->kickClient(this);
		return -1;
	}else
	{
		return ret;
	}
};

}
}
