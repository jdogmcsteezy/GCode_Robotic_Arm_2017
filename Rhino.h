#ifndef RHINO_H
#define RHINO_H
#include <iostream>
#include <cMath>
#include <iomanip>
#include "tserial.h"
#include "Kinematics.h"
#include "Line.h"
#include "circle.h"

enum Motors{C = 67,
			D = 68,
			E = 69,
			F = 70,};


class Rhino
{
private:
	Tserial Robot;
	Kinematics math;
	Line line;

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
	bool sendCommands(const Motors motor, int count);

	Rhino(char* comPort,const double armOne,const double armTwo);

	void home();

	bool moveTo(const PointXY &newPt);

	bool moveTo_Line(const PointXY &newPt, double resolution);

	void operator << ( char* const ptr){Robot << ptr;};


};

#endif