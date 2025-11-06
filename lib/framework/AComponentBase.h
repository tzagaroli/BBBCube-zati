/**
 * @file	AComponentBase.h
 * @author	Michael Meindl
 * @date	5.10.2016
 */
#ifndef ACOMPONENTBASE_H
#define ACOMPONENTBASE_H
#include "Config.h"
#include "IRunnable.h"

class CProxy;

class AComponentBase : public IRunnable
{
public:
	virtual void run() = 0;
	virtual void init() = 0;
public:
	AComponentBase();
protected:
};

#endif
