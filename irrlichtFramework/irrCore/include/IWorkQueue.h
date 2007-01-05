/*
 * IWorkQueue.h - A first in first out work queue.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_WORK_QUEUE_H_INCLUDED__
#define __IRR_WORK_QUEUE_H_INCLUDED__

#include <irrList.h>
#include <IJob.h>

namespace irr
{
namespace core
{

	class IWorkQueue
	{
	public:

		IWorkQueue()
		: JobsPending(0), JobsDone(0)
		{
			Jobs = new list<IJob*>();
		};

		virtual ~IWorkQueue() 
		{
			delete Jobs;
		};

		virtual void addJob(IJob* job) = 0;

		virtual void doNextJob() = 0;

		u32 JobsPending;
		u32 JobsDone;

	protected:

		list<IJob*>* Jobs;

	};

}
}

#endif
