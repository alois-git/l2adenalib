#include <CLoginServer.h>
#include <CGameServer.h>
#include <irrNet.h>
#include <iostream>
#include <CReadFile.h>

using namespace std;

int main()
{
	irr::net::Address a("192.168.0.2", "2106");
	irr::net::Address a2("192.168.0.2", "7777");
	adena::login_server::CLoginServer* s = new adena::login_server::CLoginServer(a);
	s->start();
	adena::game_server::CGameServer* g = new adena::game_server::CGameServer(a2);
	g->start();
	while(s->Running)
		irr::core::threads::sleep(10);
	system("PAUSE");
	irr::net::Cleanup();
	return 0;
}
