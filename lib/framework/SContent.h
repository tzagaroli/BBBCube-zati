/**
 * @author	Michael Meindl
 * @date	8.12.2016
 * @brief	Structure to hold all the content of the CContainer.
 */
#ifndef SCONTENT_H
#define SCONTENT_H
#include "SStateVectorData.h"
#include "Global.h"
#include "CIMUData.h"

struct SContent
{
	Int64 mTimeUs;
	CIMUData mSensor1Data;
	CIMUData mSensor2Data;
	SStateVectorData mStateData;
	float mMotorTorque;
	UInt16 mADCValue;
	UInt16 mPadding;
};

#endif
