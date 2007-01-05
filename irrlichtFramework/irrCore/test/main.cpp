#include <irrCore.h>
#include <iostream>

using namespace std;

using namespace irr;
using namespace core;

int main()
{
	ByteStream<> a = ByteStream<>();
	a.w32(100);
	cout << a.getSize() << " " << a.r32() << "\n";
	system("PAUSE");
	return 0;
}