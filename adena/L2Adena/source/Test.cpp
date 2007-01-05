#include <CLoginServer.h>
#include <irrNet.h>
#include <iostream>
#include <CReadFile.h>

using namespace std;

int main()
{
	irr::net::Address a("192.168.0.2", "2106");
	adena::CLoginServer* s = new adena::CLoginServer(a);
	s->start();
	while(s->Running)
		irr::core::threads::sleep(10);
	system("PAUSE");
	irr::net::Cleanup();
	return 0;
}
