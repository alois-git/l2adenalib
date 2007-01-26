#include <irrCore.h>
#include <CGc.h>
#include <iostream>

using namespace std;

using namespace irr;
using namespace core;

class c : public gc
{
public:
	c()
	{

	}

	virtual ~c()
	{

	}

	irr::u32 Var;
};

int main()
{
	c* hi = NULL;
	for(int i = 0; i < 20; i++)
		hi = new c();
	cout << hi->Var << "\n";
	gc::garbageCollect();
	delete hi;
	system("PAUSE");
	return 0;
}