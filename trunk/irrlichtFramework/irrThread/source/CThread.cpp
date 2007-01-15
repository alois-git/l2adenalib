/*
 * irrThread.cpp - irrThread.
 * Created November 6, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <CThread.h>
#include <os.h>

static void* startThread(void* t)
{
	((irr::core::threads::Thread*)t)->run();
	((irr::core::threads::Thread*)t)->Running = false;
	return NULL;
}

namespace irr
{
namespace core
{
namespace threads
{

void sleep(u32 m_seconds)
{
	os::Sleep::sleep(m_seconds);
}

Thread::Thread()
: Running(false)
{

};

void Thread::start()
{
	pthread_create((pthread_t*)&ThreadHandle, NULL, startThread, this);
	Running = true;
};

void Thread::stop()
{
	exit();
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
	pthread_join((pthread_t)ThreadHandle, NULL);
};

}
}
}
