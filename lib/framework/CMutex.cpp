/**
 * @file CBinarySemaphore.cpp
 * @author Michael Meindl
 * @date 24.9.2016
 * @brief Method definitions for a mutex.
 */
#include "CMutex.h"
#include "Assertion.h"
#include <pthread.h>
#include <iostream>


CMutex::CMutex(bool isAvailable, bool isProcessShared)
{
	pthread_mutexattr_t attr;
	Int32 retVal = pthread_mutexattr_init(&attr);
	sAssertion(0 == retVal, "(CMutex::CMutex()): Failed to initialize attributes", true);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	retVal = pthread_mutexattr_setpshared(&attr,
										  isProcessShared ? PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE);
	sAssertion(0 == retVal, "(CMutex::CMutex()): Failed to set attributes", true);

	retVal = pthread_mutex_init(&mMutex, &attr);
	sAssertion(0 == retVal, "(CMutex::CMutex()): Failed to initialize the mutex", true);

	if(false == isAvailable)
	{
		pthread_mutex_lock(&mMutex);
	}
	pthread_mutexattr_destroy(&attr);
}
bool CMutex::take(bool waitForever)
{
	bool haveSem = (0 == pthread_mutex_trylock(&mMutex));

	if((false == haveSem) && (true == waitForever))
	{
		haveSem = (0 == pthread_mutex_lock(&mMutex));
	}
	return haveSem;
}
void CMutex::give()
{
	Int32 retVal = pthread_mutex_unlock(&mMutex);
	sAssertion(0 == retVal, "(CMutex::give()): Failed to unlock the mutex", true);
}
CMutex::~CMutex()
{
	pthread_mutex_destroy(&mMutex);
}
