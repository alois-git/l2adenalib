/*
 * irrThread.cpp - irrThread.
 * Created November 6, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <CThread.h>

#ifdef _IRR_WINDOWS_
#include <windows.h>
#include <process.h>
#else
#include <pthread.h>
#endif

#ifdef _IRR_WINDOWS_
static void startThread(void* t)
#else
static void* startThread(void* t)
#endif
{
	((irr::core::threads::Thread*)t)->run();
	((irr::core::threads::Thread*)t)->Running = false;
}

namespace irr
{
namespace core
{
namespace threads
{

void sleep(u32 m_seconds)
{
	::Sleep(m_seconds);
}

Thread::Thread()
: Running(false)
{

};

void Thread::start()
{
#ifdef _IRR_WINDOWS_
	ThreadHandle = (u32)_beginthread(startThread, NULL, this);
#else
	pthread_create((pthread_t*)&ThreadHandle, NULL, startThread, this);
#endif
	Running = true;
};

void Thread::stop()
{
	exit();
#ifdef _IRR_WINDOWS_

#else

#endif
};
/*
void Thread::pause()
{
#ifdef _IRR_WINDOWS_
	SuspendThread(ThreadHandle);
#else
	
#endif
};

void Thread::resume()
{

};
*/
bool Thread::running()
{
	return Running;
};

void Thread::wait()
{
#ifdef _IRR_WINDOWS_
	WaitForSingleObject((HANDLE)ThreadHandle, INFINITE);
#else
	pthread_join((pthread_t)ThreadHandle, NULL);
#endif
};

}
}
}
