/**
 * @file CBinarySemaphore.cpp
 * @author Michael Meindl
 * @date 24.9.2016
 * @brief Method definitions for a binary semaphore, which is simulated using a mutex.
 */
#include "CBinarySemaphore.h"
#include "Assertion.h"

CBinarySemaphore::CBinarySemaphore(bool isAvailable, bool isProcessShared) : mCounter(1)
{
	Int32 retVal;
	pthread_mutexattr_t mutexAttr;
	retVal = pthread_mutexattr_init(&mutexAttr);
	sAssertion(0 == retVal, "(CBinarySemaphore::CBinarySemaphore()) : Failed to init Mutex-Attribute!", true);

	retVal = pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_ERRORCHECK);
	sAssertion(0 == retVal, "(CBinarySemaphore::CBinarySemaphore()) : Failed to set Mutex-Type!", true);

	retVal = pthread_mutex_init(&mMutex, &mutexAttr);
	sAssertion(0 == retVal, "(CBinarySemaphore::CBinarySemaphore()) : Failed to init Mutex!", true);

	retVal = pthread_mutexattr_destroy(&mutexAttr);
	sAssertion(0 == retVal, "(CBinarySemaphore::CBinarySemaphore()) : Failed to destroy Mutex-Attribute!", true);

	pthread_condattr_t conditionAttr;
	retVal = pthread_condattr_init(&conditionAttr);
	sAssertion(0 == retVal, "(CBinarySemaphore::CBinarySemaphore()) : Failed to init Condition-Attribute!", true);

	retVal = pthread_condattr_setpshared(&conditionAttr,
										 isProcessShared ? PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE);
	sAssertion(0 == retVal, "(CBinarySemaphore::CBinarySemaphore()) : Failed to set Condition-Attribute!", true);

	pthread_cond_init(&mCondition, &conditionAttr);
	pthread_condattr_destroy(&conditionAttr);


	if(false == isAvailable)
	{
		mCounter = 0;
	}
}
CBinarySemaphore::~CBinarySemaphore()
{
	pthread_mutex_destroy(&mMutex);
}
bool CBinarySemaphore::take(bool waitForever)
{
	bool result = true;
	pthread_mutex_lock(&mMutex);
	if(1 == mCounter)
	{
		mCounter = 0;
	}
	else if(false == waitForever)
	{
		result = false;
	}
	else
	{
		while(0 == mCounter)
		{
			pthread_cond_wait(&mCondition, &mMutex);
		}
		mCounter = 0;
	}
	pthread_mutex_unlock(&mMutex);
	return result;
}
void CBinarySemaphore::give()
{
	pthread_mutex_lock(&mMutex);
	mCounter = 1;
	pthread_mutex_unlock(&mMutex);
	pthread_cond_signal(&mCondition);
}
