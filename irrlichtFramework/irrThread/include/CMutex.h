/*
 * CMutex.h - irrThread.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_CMUTEX_H_INCLUDED__
#define __IRR_CMUTEX_H_INCLUDED__

#include <irrCore.h>
#include <irrThreadCompile.h>

namespace irr
{
namespace core
{
namespace threads
{	

	class IRRTHREAD_API Mutex
	{
	public:

		Mutex();

		~Mutex();

		void getLock();

		void releaseLock();

	private:

		#ifdef _IRR_WINDOWS_
		CRITICAL_SECTION MutexHandle;
		#else
		pthread_mutex_t MutexHandle;
		#endif
	};

}
}
}

#endif
