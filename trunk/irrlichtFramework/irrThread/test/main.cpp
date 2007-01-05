#include <irrThread.h>
#include <time.h>
#include <iostream>

using namespace std;
using namespace irr;
using namespace core;
using namespace threads;

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

class MyJob : public IJob
{
public:

	MyJob(int num)
	: Num(num)
	{
		m = new Mutex();
	};

	virtual ~MyJob()
	{
	
	};

	bool isPrime(u32 p)
	{
		int d;
		int sqrtp = (int)sqrt((double)p);

		for (d = 2; d < sqrtp; d = d + 1)
		if (p % d == 0)
			return false;

		return true;
	}

	virtual void doJob()
	{
		while(true)
		{
			m->getLock();
			int n = Num;
			Num ++;
			if(Num >= 510000)
			{
				m->releaseLock();
				return;
			}
			m->releaseLock();
			if(isPrime(n))
			{
				//cout << n << " is prime!\n";
			}else
			{
				// ...
			}
		}
	};

	Mutex* m;

	int Num;

};

int main()
{
	CThreadPool* tp = new CThreadPool();
	IJob* j;
	for(int i = 1; i <= 10; i++)
	{
		tp->setThreadCount(i);
		j = new MyJob(500000);
		for(int ii = 0; ii < i; ii++)
		{
			tp->addJob(j);
			cout << tp->JobsPending << "\n";
		}
		delete j;
		cout << "Done!\n";
	}
	system("PAUSE");
	return 0;
}
