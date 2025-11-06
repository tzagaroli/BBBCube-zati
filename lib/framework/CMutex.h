/*
 * @file CBinarySemaphore.h
 * @author Michael Meindl
 * @date 18.9.2016
 * @brief Class definition for a mutex.
 */
#ifndef CMUTEX_H
#define CMUTEX_H
#include "Global.h"
#include <pthread.h>

class CMutex
{
public:
	bool take(bool waitForever);
	void give();
public:
	CMutex(bool isAvailable = true, bool isProcessShared = false);
	~CMutex();
private:
	CMutex(const CMutex&);					// to avoid misuse
	CMutex& operator=(const CMutex&);		// to avoid misuse
	pthread_mutex_t mMutex;
};


#endif
