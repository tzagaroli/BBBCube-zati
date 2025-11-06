/*
 * SCalibData.h
 *
 *  Created on: Q1 22
 *      Author: JW
 */

#ifndef LIB_SCALIBDATA_H_
#define LIB_SCALIBDATA_H_
#include "Global.h"

#define WUERFEL 5

// globals
const float T_a = 0.02;						// Abtastfrequenz	= 50 Hz;
const Int32 CombFilterIndexMax(8);			// 8
const float SensorAlpha(0.14/0.061);		// geometrie zwischen Sensoren
const float ComplementaryAlpha(0.98);		// fuer CompFilter
const float F[] = {-2.1431F, -0.2186F, -0.0013F};	// Zustandsregler  von Meindl  im Regler ein vorgestelltes Minus



class SCalibData
{
public:
	SCalibData();
	float X1_dd_P1;			// Kx1
	float X1_dd_P2;			// Offset_x1
	float Y1_dd_P1;			// kY1
	float Y1_dd_P2;			// Offset_y1

	float X2_dd_P1;			// Kx2
	float X2_dd_P2;			// Offset_x2
	float Y2_dd_P1;			// kY2
	float Y2_dd_P2;			// Offset_y2
	float Phi1_d_P1;		// Kphi1
	float Phi1_d_P2;		// Offset_phi1

	float Phi2_d_P1;		// Kphi2
	float Phi2_d_P2;		// Offset_phi2

	float PSI_d_P1;			// K_ADC
	float PSI_d_P2;			// Offset_ADC

	float man_correction;

};



#endif /* LIB_SCALIBDATA_H_ */
