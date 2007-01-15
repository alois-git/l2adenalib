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
: MutexHandle(PTHREAD_MUTEX_INITIALIZER)
{

};

Mutex::~Mutex()
{
	pthread_mutex_destroy(&MutexHandle);
};

void Mutex::getLock()
{
	pthread_mutex_lock(&MutexHandle);
};

void Mutex::releaseLock()
{
	pthread_mutex_unlock(&MutexHandle);
};

}
}
}
