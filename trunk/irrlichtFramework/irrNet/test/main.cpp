#include <irrNet.h>
#include <iostream>
#include <CReadFile.h>

using namespace std;

using namespace irr;
using namespace net;
using namespace core;

class MyNetEvent : public INetEvent
{
public:
	MyNetEvent()
	{
		
	};

	~MyNetEvent()
	{

	};

	void OnEvent(NetEvent &e)
	{
		cout << "Event!\n";
		switch(e.enet)
		{
			case ENET_CLIENT_CONNECT:
				cout << "Client connected\n";
				break;
			case ENET_CLIENT_DISCONNECT:
				cout << "Client disconnected\n";
				break;
			case ENET_RECVDATA:
				cout << "Recved data\n";
				//hexdump(e.recvData.data, e.recvData.dataLen);
				c8 buff[1024];
				s32 len = e.serverClient->recv(buff, 1024);
				hexdump(buff, len);
				if(e.ec == EC_SERVER)
				{
					c8 data[] = "HTTP/1.0 200 OK\r\n\
Date: Fri, 31 Dec 1999 23:59:59 GMT\r\n\
Content-Type: text/plain\r\n\
\r\n";
					e.serverClient->send(data, sizeof(data));
					e.server->setMaxUpSpeedPerClient(10240);
					io::CReadFile rf("C:\\Downloads\\bf2_patch1.3.exe");
					if(!rf.isOpen())
						cout << "Failed to open file...\n";
					c8 sb[2048];
					while(true)
					{
						int read = rf.read(sb, 2048);
						if(!read)
							break; // EOF
						e.serverClient->send(sb, read);
					}
					e.server->kickClient(e.serverClient);
				}
				break;
		}
	};
};

int main()
{
	MyNetEvent ne = MyNetEvent();
	IServer* s = new CTCPServer(&ne, 10);
	//Bind to all addresses on current system.
	Address a("127.0.0.1","80");
	for(u32 i = 0; i < a.length(); i++)
	{
		cout << a[i].addr.c_str() << "\n";
	}
	s->bind(a);
	s->start();

	/*IClient* s = new CTCPClient(&ne);
	if(!s->connect(Address("192.168.0.52", "80")))
	{
		cout << "Connecting to bigcheeseservers.com failed.\n";
	}
	s->start();
	c8 b[] = "GET / HTTP/1.0\r\n\
From: someuser@jmarshall.com\r\n\
User-Agent: HTTPTool/1.0\r\n\
\r\n";
	s->send(b, sizeof(b));*/
	while(s->Running)
		threads::sleep(10);
	system("PAUSE");
	Cleanup();
	return 0;
}