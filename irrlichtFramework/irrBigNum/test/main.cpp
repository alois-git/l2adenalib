#include <irrCore.h>
#include <irrBigNum.h>
#include <iostream>

using namespace std;

using namespace irr;
using namespace core;
using namespace math;

ostream& operator <<(ostream& stream, BigNum &a)
{
	a.print();
	return stream;
};

int main()
{
	cout << "====== irrBigNum 1.0 unit test ======\n";

	// Constructor test.

	cout << "------ constructor test... ";
	BigNum a(20);
	BigNum b(10);
	do
	{
		if(a != BigNum(20)){
			cout << "failed... a != 20\n";
			break;
		}
		if(b != BigNum(10)){
			cout << "failed... b != 10\n";
			break;
		}
		cout << "passed ------\n";

		// Addition test.

		cout << "------ addition test... ";
		if(a + b != BigNum(30)){
			cout << "failed... a + b != 30\n";
			break;
		}
		cout << "passed ------\n";

		// < > test.

		cout << "------ < > test... ";
		if(b > a){
			cout << "failed... b > a\n";
			break;
		}
		if(a < b){
			cout << "failed... a < b\n";
			break;
		}
		cout << "passed ------\n";

		// Prime test.

		cout << "------ Prime test... ";
		a.randPrime(512);
		if(!a.isPrime(4)){
			cout << "failed... a is not prime\n";
			break;
		}
		cout << "passed ------\n";

		cout << "====== irrBigNum 1.0 unit test compleeted ======\n";
	}while(false);
	system("PAUSE");
	return 0;
}