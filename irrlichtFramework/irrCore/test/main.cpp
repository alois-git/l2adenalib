#include <irrCore.h>
#include <iostream>

using namespace std;

using namespace irr;
using namespace core;

int main()
{
	vector3df loc(11, 10, 0);
	vector3df target(19, 10, 0);
	line3df line(loc, target);
	vector3df heading = line.getVector();
	heading.setLength(133.0); // Speed.
	loc += heading;

	system("PAUSE");
	return 0;
}
