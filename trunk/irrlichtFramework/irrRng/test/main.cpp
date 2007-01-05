#include <CMersenneTwister.h>
#include <CDefaultRNG.h>
#include <iostream>
#include <time.h>

using namespace std;

using namespace irr;

int main()
{
	do{
		cout << "====== irrRng 1.0 unit test ======\n";

		IRng* rng = new CMersenneTwister();
		//IRng* rng = new CDefaultRNG();
		u32 r = time(NULL);
		rng->seed(&r, 1);

		//! Generating numbers.

		cout << "------ Generating random numbers ------\n";
		cout << "------ getRandS32(min, max)\n";

		for(int i = 1; i <= 10; i++)
		{
			cout << rng->getRandS32(-10, 10) << " ";
			if((i % 5) == 0)
				cout << "\n";
		}

		cout << "------ getRandU32()\n";

		for(int i = 1; i <= 10; i++)
		{
			cout << rng->getRandU32() << " ";
			if((i % 5) == 0)
				cout << "\n";
		}

		cout << "------ getRandBuffer(buffer, len)\n"; 

		c8 buffer[10];
		rng->getRandBuffer(buffer, 10);
		for(int i = 1; i <= 10; i++)
		{
			cout << (int)buffer[i - 1] << " ";
			if((i % 5) == 0)
				cout << "\n";
		}

		cout << "------ Worked ------\n";
		cout << "====== irrRng 1.0 unit test compleeted ======\n"; 
	}while(false);
	system("PAUSE");
	return 0;
}