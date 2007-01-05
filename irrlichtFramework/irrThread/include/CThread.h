/*
 * CThread.h - irrThread.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_CTHREAD_H_INCLUDED__
#define __IRR_CTHREAD_H_INCLUDED__

#include <irrCore.h>
#include <irrThreadCompile.h>

namespace irr
{
namespace core
{
namespace threads
{

	void IRRTHREAD_API sleep(u32 m_seconds);

	class IRRTHREAD_API Thread
	{
	public:

		Thread();

		virtual ~Thread() {}

		//! Thread function.
		virtual void run() = 0;

		//! Called before thread is destroyed.
		virtual void exit() {}

		//! Starts thread and calls run.
		void start();

		//! Calls exit and stops thread.
		void stop();

		//void pause();

		//void resume();

		bool running();

		//! Blocking call. Waits untill thread exits.
		void wait();

		bool Running;

	private:

		u32 ThreadHandle;
	};

}
}
}

#endif
