#include <iostream>
#include <irrThread.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace threads;

class MyThread : public Thread
{
private:

	irr::u32 T;

public:

	MyThread(irr::u32 tid)
	: T(tid)
	{

	};

	~MyThread()
	{

	};

	virtual void run()
	{
		static Mutex m = Mutex();
		for(int i = 0; i < 10; i++)
		{
			m.getLock();
			cout << "Hi im thread number " << T << "!\n";
			m.releaseLock();
		}
	};

};

int main()
{
	MyThread** t = new MyThread*[20];
	for(int i = 0; i < 5; i++)
	{
		t[i] = new MyThread(i);
		t[i]->start();
	}
	for(int i = 0; i < 5; i++)
	{
		t[i]->wait();
	}
	char c;
	cin >> c;
	return 0;
}