//************************************************************************//
// Copyright © 2017, Jesse Schmidt //
// All rights reserved. //
// //
// Author: //
// Jesse Schmidt //
// //
// Department: //
// COMSC-11 C++ Programming Department //
// //
// Purpose: Containts all aspects to successfully //
//			control the Rhino robot.					//
// //
// //
// Revision History //
// 05/19/2017 Jesse Schmidt //
// - Original Version //
// //
//************************************************************************//
#ifndef RHINO_H
#define RHINO_H
#include <cMath>
#include <iomanip>
#include "tserial.h"
#include "Kinematics.h"
#include "Line.h"
#include "circle.h"
#include <iostream>

using namespace std;

enum Motors{C = 67,
			D = 68,
			E = 69,
			F = 70,};

enum Rotation{CW, CCW};

class Rhino
{
private:
	int connectError;
	Tserial Robot;
	Kinematics math;
	Line line;
	Circle circle;

	Rotation OnRotate;

	Angles armCounts;
	Angles nextAngles;

	PointXY currentXY;

	const int Home = 750;
	double armOne;
	double armTwo;


	bool switchStatus(const Motors check);
	int motorCount(const Motors check);
	void toTicks(Angles &convert);
	

public:
	Rhino(const char* comPort, Rotation OnRotate = CCW);

	bool connect(const char* comPort){ return connectError = Robot.connect(comPort, 9600, spEVEN); }

	bool isConnected() { return (connectError) ? false : true; } //let you know if comport is connected

	void setRotate(Rotation OnRotate){ this->OnRotate = OnRotate; }

	bool sendCommands(const Motors motor, int count);

	void home();

	bool moveTo(const PointXY &newPt);

	bool moveTo_Line(const PointXY &newPt, double resolution);

	bool moveTo_Arc(const PointXY &newPt, const PointXY &center, const double resolution, const Rotation rotate);

	bool move_OnOff(int OnOff);

	PointXY getCurrentPt() { return currentXY; }

	void operator << ( char* const ptr){Robot << ptr;}

};

#endif