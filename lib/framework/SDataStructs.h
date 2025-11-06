/*
 * SDataStructs.h
 *
 *  Created on: Jan 1, 2017
 *      Author: vmuser
 */

#ifndef LIB_SDATASTRUCTS_H_
#define LIB_SDATASTRUCTS_H_

#include "Global.h"

struct SMPU9250_32_Data			// für die alten AlignProgramme
{
public:
	Int32 mX_dd;		//! Sensor  X-Acceleration []
	Int32 mY_dd;		//! Sensor  Y-Acceleration []
	Int32 mPhi_d;		//! Sensor  Z-Angular Velocity []
};


struct SMPU9250Data
{
public:
	Int16 mX_dd;		//! Sensor  X-Acceleration []
	Int16 mY_dd;		//! Sensor  Y-Acceleration []
	Int16 mPhi_d;		//! Sensor  Z-Angular Velocity []
	Int16 mPadding;
};

struct SMPU9250Data_f_Data
{
public:
	float mX_dd;		//! Sensor  X-Acceleration []
	float mY_dd;		//! Sensor  Y-Acceleration []
	float mPhi_d;		//! Sensor  Z-Angular Velocity []
};

struct SMPU9250_Calibrated_Data
{
public:
	float mX_dd;		//! Sensor  X-Acceleration []
	float mY_dd;		//! Sensor  Y-Acceleration []
	float mPhi_d;		//! Sensor  Z-Angular Velocity []
	float mPsi_d;		//! Motor ADC
};

struct SMPU9250_Calculated_Data
{
public:
	float mPhi_A;			//! Phi-Value from the acceleration-estimate [rad]
	float mPhi_d_G;		//! Phi-Value from the gyroscope geometric integration [rad]
	float mPsi_d;			//! Psi__d-Vallue from the ADC	[rad/sec]
};

struct SMPU9250_Filtered_Data
{
public:
	float mPhi;				//! Phi-Value from the complementaryfilter [rad]
	float mPhi_d;			//! Phi__d-Value from the gyroscopes [rad/sec]
	float mPsi_d;			//! Psi__d-Vallue from the ADC	[rad/sec]
};



#endif /* LIB_SDATASTRUCTS_H_ */
