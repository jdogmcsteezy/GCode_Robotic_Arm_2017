#include "Line.h"
#include<iostream>

//CONSTRUCTOR
Line::Line()
{
	start = { 0 };
	end = { 0 };
}

//CONSTRUCTOR(OVERLOAD)
//	Takes two arguments of PointXY start point,
//	end point. Assigns it to object.
Line::Line(const PointXY A, const PointXY B)
{
	start = A;
	end = B;
}

//SETPOINT
//	Assigns arguments PointXY start and end
//	to object.
void Line::setPoints(PointXY A, PointXY B)
{
	start = A;
	end = B;
}

//GETDISTANCE
//	Returns distance between start and end point.
double Line::getDistance()
{
	return sqrt(pow((start.ptX - end.ptX), 2) + pow((start.ptY - end.ptY), 2));
}

//GETTHETA
//	Returns angle in radians of start point in
//	reference to end point. Angle is in reference.
double Line::getTheta()
{

	return atan((start.ptY - end.ptY) / (start.ptX - end.ptX));
}

//GETNEXTSTEP
//	Returns next PointXY with argument of 
//	double hypotenuse length.
PointXY Line::getNextPt(const double nextStep)
{
	PointXY returnXY;
	double theta = getTheta();

	(abs(theta) == (90 * (M_PI / 180))) ? theta = -theta : theta;

	returnXY.ptX = (nextStep * cos(theta));
	returnXY.ptY = (nextStep * sin(theta));

	if (end.ptX < start.ptX)
	{
		returnXY.ptX = -returnXY.ptX;
		returnXY.ptY = -returnXY.ptY;
	}

		returnXY.ptX += start.ptX;
		returnXY.ptY += start.ptY;
		returnXY.ptZ = start.ptZ;

	return returnXY;

}

