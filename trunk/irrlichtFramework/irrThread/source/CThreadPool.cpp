/*
 * CThreadPool.cpp - Thread pool.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <CThreadPool.h>

namespace irr
{
namespace core
{
namespace threads
{

CThreadPool::CThreadPool()
: IWorkQueue(), paused(false)
{
	Threads = array<CJobThread*>();
	JobsMutex = new Mutex();
};

CThreadPool::~CThreadPool()
{
	JobsMutex->getLock();
	for(u32 i = 0; i < Threads.size(); i++)
	{
		delete Threads[i];
	}
	JobsMutex->releaseLock();
	delete JobsMutex;
};

void CThreadPool::addJob(IJob* job)
{
	job->JobState = EJS_PENDING;
	JobsPending++;
	JobsMutex->getLock();
	Jobs->push_back(job);
	JobsMutex->releaseLock();
};

void CThreadPool::doNextJob() {};
/*
{
	while(true)
	{
		JobsMutex->getLock();
		if(!Jobs->empty())
		{
			JobsMutex->releaseLock();
			break;
		}
		JobsMutex->releaseLock();
		sleep(10);
	}

	JobsMutex->getLock();
	list<IJob*>::Iterator ittr(Jobs->begin());

	for(int i = 0; i < Threads.size(); i++)
	{
		if(!Threads[i]->Running)
		{
			Threads[i]->run((*ittr));
			Jobs->erase(ittr);
			break;
		}
	}

	JobsMutex->releaseLock();
};*/

void CThreadPool::setThreadCount(u32 threads)
{
	u32 size = Threads.size();
	Threads.set_used(threads);
	if(size > threads)
	{
		u32 i;
		for(i = threads; i < size; i++)
		{
			delete Threads[i];
		}
	}else
	{
		u32 i;
		for(i = size; i < threads; i++)
		{
			Threads[i] = new CJobThread(this, Jobs, JobsMutex);
			Threads[i]->start();
		}
	}
};

u32 CThreadPool::jobsLeft()
{
	JobsMutex->getLock();
	return Jobs->getSize();
	JobsMutex->releaseLock();
};

void CThreadPool::pause()
{
	paused = true;
};

void CThreadPool::unpause()
{
	paused = false;
};

}
}
}
