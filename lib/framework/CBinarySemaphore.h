/*
 * @file CBinarySemaphore.h
 * @author Michael Meindl
 * @date 18.9.2016
 * @brief Class definition for a binary semaphore, which is sumulated using a mutex.
 */
#ifndef CBINARYSEMAPHORE_H
#define CBINARYSEMAPHORE_H
#include "Global.h"
#include <pthread.h>

class CBinarySemaphore
{
public:
	bool take(bool waitForever);
	void give();
public:
	CBinarySemaphore(bool isAvailable, bool isProcessShared);
	~CBinarySemaphore();
private:
	pthread_mutex_t mMutex;
	pthread_cond_t mCondition;
	Int32 mCounter;
};

#endif
