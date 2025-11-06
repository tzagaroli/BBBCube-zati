/*
 * SCalibData.cpp
 *
 *  Created on: Dec 31, 2016
 *      Author: vmuser
 */
#include <SCalibData.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   2022 , neuer Würfel 1 , 18.5.22, siehe Excel dann nachgearbeitet
#if WUERFEL==1

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(0.1F),					// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.08F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(-0.01F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.13F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset
// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		//

								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.02F),				// Offset_phi2	0.0162F geändert auf 0.0
								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(0.0084F)			// manual correction des finalen Winkels phi
#endif

#if WUERFEL==2
//   2022 , neuer Würfel 2 , 18.5.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(0.20F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.12F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2( 1.16F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.74F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset
// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),			// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-156.0F),				// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(-0.01)			// manual correction des finalen Winkels phi
#endif

#if WUERFEL==3
//   2022 , neuer Würfel 3 , 18.5.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(+0.02F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(-0.02F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(+0.05F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.093F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset
// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),			// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(-0.01)			// manual correction des finalen Winkels phi
#endif

#if WUERFEL==4

//   2022 , neuer Würfel 4 , 18.5.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(+0.04F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.03F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(+0.16F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.17F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset
// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),			// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(-0.01)			// manual correction des finalen Winkels phi

#endif

#if WUERFEL==5
//   2022 , neuer Würfel 5 , 25.4.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(+0.1F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.11F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(+0.15F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(-0.07F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset

								// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),			// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(+0.01)			// manual correction des finalen Winkels phi
#endif

#if WUERFEL==6

 //   2022 , neuer Würfel 6 , 25.4.22, siehe Excel dann nachgearbeitet
  SCalibData::SCalibData():
 								X1_dd_P1(-0.0012F),				// Kx1
 								X1_dd_P2(+0.18F),				// Offset_x1				das ist für y = kx + offset
 								Y1_dd_P1(-0.0012F),				// kY1
 								Y1_dd_P2(+0.16F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

 								X2_dd_P1(-0.0012F),				// Kx2
 								X2_dd_P2(-0.13F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
 								Y2_dd_P1(-0.0012F),				// kY2
 								Y2_dd_P2(+0.16F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset

 // Drehratensensoren
 								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
 																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
 																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
 																// -0.0076*2*pi/360 = -0.000133
 								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

 								Phi2_d_P1(-0.001063686F),		// Kphi2
 								Phi2_d_P2(-0.00409519F),			// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(-0.01)			// manual correction des finalen Winkels phi
#endif

#if WUERFEL==7

//   2022 , neuer Würfel 7 , 25.4.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(-0.02F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(-0.0F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(-0.16F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.1F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset
// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),		// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(-0.01)			// manual correction des finalen Winkels phi
#endif

#if WUERFEL==8

//   2022 , neuer Würfel 8 , 18.5.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(+0.52F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.54F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(-0.10F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.08F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset
// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),			// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(-0.01)			// manual correction des finalen Winkels phi

#endif

#if WUERFEL==9
//   2022 , neuer Würfel 9 , 25.4.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(-0.1F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.0F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(-0.1F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.1F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset

// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),			// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(+0.05)			// manual correction des finalen Winkels phi

#endif

#if WUERFEL==10
//   2022 , neuer Würfel 10 , 28.4.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(-0.18F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.2F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(+0.34F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.27F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset

// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(+0.10F),				// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(+0.01)			// manual correction des finalen Winkels phi

#endif

#if WUERFEL==11
//   2022 , neuer Würfel 11 , 25.4.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(+0.1F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.09F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(+0.1F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.1F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset

// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(-0.004F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.000F),				// Offset_phi2

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(+0.01)			// manual correction des finalen Winkels phi
#endif

#if WUERFEL==12
// 2022 , neuer Würfel 12 , 22.4.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(+0.1F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.08),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(-0.01F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.13F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset

// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(-0.032442412F),		// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),		// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(+0.0)			// manual correction des finalen Winkels phi
#endif

#if WUERFEL==13
// 2022 , neuer Würfel 13 , 25.4.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(-0.015F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.16F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(0.25F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.2F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset

// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),		// Offset_phi2	0.0162F geändert auf 0.0

								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(+0.04)			// manual correction des finalen Winkels phi

#endif

#if WUERFEL==14
// 2022 , neuer Würfel 14 , 25.4.22, siehe Excel dann nachgearbeitet

SCalibData::SCalibData():
								X1_dd_P1(-0.0012F),				// Kx1
								X1_dd_P2(-0.05F),				// Offset_x1				das ist für y = kx + offset
								Y1_dd_P1(-0.0012F),				// kY1
								Y1_dd_P2(+0.15F),				// Offset_y1				das ist für y = kx + offset 0.5152F auf 0.1 abgeändert

								X2_dd_P1(-0.0012F),				// Kx2
								X2_dd_P2(-0.24F),				// Offset_x2	-0.1032F auf 0.6 geändert			das ist für y = kx + offset
								Y2_dd_P1(-0.0012F),				// kY2
								Y2_dd_P2(+0.12F),				// Offset_y2	0.01566 auf 0.1 geändert			das ist für y = kx + offset



// Drehratensensoren
								Phi1_d_P1(-0.001063686F),		// prüfen  Kphi1 warum mal 8	8*-0.000133231, 12 Bit Werte auf 15 Bit +VZ skalieren
																// Kphi1	-0.0076,kommt aus dem Datenblatt, Sensorwerte °/s,
																// wir möchten SI-Einheiten also rad/s, deswegen noch Faktor 2*pi/360 dazu.
																// -0.0076*2*pi/360 = -0.000133
								Phi1_d_P2(+0.01F),				// Offset_phi1				das ist für y = kx + offset  0.0471F geändert auf 0.02

								Phi2_d_P1(-0.001063686F),		// Kphi2
								Phi2_d_P2(-0.00409519F),		// Offset_phi2	0.0162F geändert auf 0.0
								PSI_d_P1(0.076F),				//0.511067708F),		// K_ADC		das ist für y = kx + offset
								PSI_d_P2(-155.0F),				//-1042.0F)		// Offset_ADC, 12 Bit Wandler nach Beobachtung abgeändert auf 1043, dann macht er die 0
								man_correction(+0.04)			// manual correction des finalen Winkels phi

#endif
{};





