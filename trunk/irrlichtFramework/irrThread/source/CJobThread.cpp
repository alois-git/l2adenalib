/*
 * CJobThread.cpp - Thread for thread pool.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <CJobThread.h>

namespace irr
{
namespace core
{
namespace threads
{

CJobThread::CJobThread(IWorkQueue* workQ, list<IJob*>* jobsList, Mutex* jobsMutex)
: JobsList(jobsList), JobsMutex(jobsMutex), parent(workQ)
{

};

CJobThread::~CJobThread()
{

};

void CJobThread::run()
{
	while(true)
	{
		JobsMutex->getLock();
		if(!JobsList->empty())
		{
			list<IJob*>::Iterator ittr(JobsList->begin());
			IJob* job = *ittr;
			JobsList->erase(ittr);
			JobsMutex->releaseLock();
			job->JobState = EJS_RUNNING;
			job->doJob();
			parent->JobsPending--;
			parent->JobsDone++;
			job->JobState = EJS_DONE;
		}else
		{
			JobsMutex->releaseLock();
			sleep(10);
		}
	}
};

void CJobThread::exit()
{

};

}
}
}
