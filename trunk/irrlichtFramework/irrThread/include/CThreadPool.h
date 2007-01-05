/*
 * CThreadPool.h - Thread pool.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_THREAD_POOL_H_INCLUDED__
#define __IRR_THREAD_POOL_H_INCLUDED__

#include <IWorkQueue.h>
#include <CJobThread.h>
#include <CMutex.h>
#include <irrArray.h>
#include <irrThreadCompile.h>

namespace irr
{
namespace core
{
namespace threads
{

	class IRRTHREAD_API CThreadPool : public IWorkQueue
	{
	public:

		CThreadPool();

		virtual ~CThreadPool();

		virtual void addJob(IJob* job);

		virtual void doNextJob();

		virtual void setThreadCount(u32 threads);

		virtual u32 jobsLeft();

		virtual void pause();

		virtual void unpause();

	protected:

		Mutex* JobsMutex;

		bool paused;

		array<CJobThread*> Threads;

	};

}
}
}

#endif
