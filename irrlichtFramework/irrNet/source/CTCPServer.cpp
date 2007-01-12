/*
* CTCPServer.h - TCP Server.
* Created 12/8/2006, by Michael 'Bigcheese' Spencer.
*/

#include <CTCPServer.h>
#include <CTCPServerClient.h>
#include <INetEvent.h>
#include <hexdump.h>

namespace irr
{
namespace net
{

CTCPServer::CTCPServer(void* eventCallBack, u32 backLog)
: IServer(eventCallBack, backLog)
{
	ClientList = core::list<IServerClient*>();
	ClientListMutex = core::threads::Mutex();
	Startup();
};

CTCPServer::~CTCPServer()
{
	if(Sock)
		::nclose(Sock);
};

void CTCPServer::run()
{
	if(Sock == 0)
		return; // You must call bind before start();

	if(::listen(Sock, BackLog) != 0)
		return;
	while(Running){
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		int blah = sizeof(sockaddr_in);
		Socket s = ::accept(Sock, (sockaddr*)&addr, &blah);
		hexdump((irr::c8*)&addr.sin_addr, 4);
		if(s != 0)
		{
			IServerClient* sc = new CTCPServerClient(s, this);
			memcpy(&sc->Addr, &addr.sin_addr, blah);
			addClient(sc);
			NetEvent ne;
			ne.serverClient = sc;
			ne.server = this;
			ne.enet = ENET_CLIENT_CONNECT;
			ne.ec = EC_SERVER;
			((INetEvent*)EventCallBack)->OnEvent(ne);
			sc->start();
		}
	}
};

u32 CTCPServer::bind(Address &a, s32 af)
{
	int error;
	if(a.resActive == 0)
	{
		addrinfo* res = a.resRoot;

		if(AddressFamily == AF_UNSPEC)
			AddressFamily = af;

		u32 binds = 0;
		for(u32 i = 0; i < a.length(); i++)
		{			
			if(AddressFamily == AF_UNSPEC)
				AddressFamily = res->ai_family;

			if(res->ai_family == AddressFamily)
			{
				if(Sock == 0)
					Sock = ::socket(AddressFamily, SOCK_STREAM, IPPROTO_TCP);
				if(error = ::bind(Sock, res->ai_addr, res->ai_addrlen) == 0)
					binds++;
				else
				{
					// TODO: Find out why i get an The operation completed successfuly error (non 0).
					//printf("%d, %s\n", &error, gai_strerror(error));
				}
			}
		}
		return binds;
	}else
	{
		if(AddressFamily == AF_UNSPEC)
			AddressFamily = a.resActive->ai_family;

		if(a.resActive->ai_family == AddressFamily)
		{
			if(Sock == 0)
				Sock = ::socket(AddressFamily, SOCK_STREAM, IPPROTO_TCP);
			if(::bind(Sock, a.resActive->ai_addr, a.resActive->ai_addrlen) == 0)
				return 1;
		}
		return 0;
	}
};

void CTCPServer::kickClient(void* client)
{
	ClientListMutex.getLock();
	((IServerClient*)client)->Running = false;
	core::list<IServerClient*>::Iterator ittr(ClientList.begin());
	bool found = false;
	for(u32 i = 0; i < ClientList.getSize(); i++)
	{
		if(*ittr == ((IServerClient*)client))
		{
			found = true;
			break;
		}
		ittr++;
	}
	ClientListMutex.releaseLock();

	if(found)
	{
		::nclose(((IServerClient*)client)->Sock);
		((IServerClient*)client)->Sock = 0;
		ClientList.erase(ittr);
		ClientListMutex.releaseLock();
		NetEvent ne;
		ne.serverClient = (IServerClient*)client;
		ne.server = this;
		ne.enet = ENET_CLIENT_DISCONNECT;
		ne.clientDisconnect.edr = EDR_KICK;
		ne.ec = EC_SERVER;
		((INetEvent*)EventCallBack)->OnEvent(ne);
	}
};

void CTCPServer::setMaxUpSpeed(u32 speed)
{

};

void CTCPServer::setMaxUpSpeedPerClient(u32 speed)
{
	ClientListMutex.getLock();
	core::list<IServerClient*>::Iterator ittr(ClientList.begin());
	for(u32 i = 0; i < ClientList.getSize(); i++)
	{
		(*ittr)->rc.setUnitsPerSecond(speed);
		ittr++;
	}
	ClientListMutex.releaseLock();
};

void CTCPServer::addClient(IServerClient *client)
{
	ClientListMutex.getLock();
	ClientList.push_back(client);
	ClientListMutex.releaseLock();
};

}
}
