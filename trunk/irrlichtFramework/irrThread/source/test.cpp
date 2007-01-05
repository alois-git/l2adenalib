#include <irrThread.h>
#include <iostream>

using namespace std;
using namespace irr;
using namespace thread;

int count = 0;

class MyThread : public Thread
{
public:
	Mutex* m;
	int n;

	MyThread(Mutex* mut, int num) : Thread()
	{
		m = mut;
		n = num;
	};

	~MyThread()
	{

	};

	virtual void run()
	{
		for(int i = 0; i < 10; i++)
		{
			m->getLock();
			cout << "Hi im thread #" << n << " and i like adena!\n";
			m->releaseLock();
		}
	};

	virtual void exit()
	{

	};
};

int main()
{
	Mutex* m = new Mutex();
	Thread* t1 = new MyThread(m, 1);
	Thread* t2 = new MyThread(m, 2);
	t1->start();
	t2->start();

	while(t1->running() || t2->running())
	{

	}
	delete m, t1, t1;
	//cout << count << "\n";
	return 0;
}
