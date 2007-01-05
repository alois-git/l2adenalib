/*
 * CJobThread.h - Thread for thread pool.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_JOB_THREAD_H_INCLUDED__
#define __IRR_JOB_THREAD_H_INCLUDED__

#include <IWorkQueue.h>
#include <CThread.h>
#include <CMutex.h>
#include <IJob.h>
#include <IEventReceiver.h>

namespace irr
{
namespace core
{
namespace threads
{

	class IRRTHREAD_API CJobThread : public Thread
	{
	public:

		CJobThread(IWorkQueue* workQ, list<IJob*>* jobsList, Mutex* jobsMutex);

		virtual ~CJobThread();

		virtual void run();

		virtual void exit();

	private:

		list<IJob*>* JobsList;

		IWorkQueue* parent;

		Mutex* JobsMutex;

	};

}
}
}

#endif
