/*
 * irrThread.cpp - irrThread.
 * Created November 6, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <CMutex.h>

#ifdef _IRR_WINDOWS_
#include <windows.h>
#include <process.h>
#else
#include <pthread.h>
#endif


namespace irr
{
namespace core
{
namespace threads
{

Mutex::Mutex()
{
	#ifdef _IRR_WINDOWS_
	InitializeCriticalSection(&MutexHandle);
	#else
	MutexHandle = PTHREAD_MUTEX_INITIALIZER;
	#endif
};

Mutex::~Mutex()
{
	#ifdef _IRR_WINDOWS_
	DeleteCriticalSection(&MutexHandle);
	#else
	#endif
};

void Mutex::getLock()
{
	#ifdef _IRR_WINDOWS_
	EnterCriticalSection(&MutexHandle);
	#else
	pthread_mutex_lock(&MutexHandle);
	#endif
};

void Mutex::releaseLock()
{
	#ifdef _IRR_WINDOWS_
	LeaveCriticalSection(&MutexHandle);
	#else
	pthread_mutex_unlock(&MutexHandle);
	#endif
};

}
}
}
