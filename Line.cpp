/* JESSE SCHMIDT 5/25/17 */
#include "Line.h"
#include<iostream>

Line::Line()
{
	start = { 0 };
	end = { 0 };
}

Line::Line(const PointXY A, const PointXY B)
{
	start = A;
	end = B;
}

double Line::getDistance()
{
	return sqrt(pow((start.ptX - end.ptX), 2) + pow((start.ptY - end.ptY), 2));
}

double Line::getTheta()
{

	return atan((start.ptY - end.ptY) / (start.ptX - end.ptX));
}

PointXY Line::getNextPt(const double nextStep)
{
	PointXY returnXY;
	double theta = getTheta();
	// Makes theta positive or negative because tan() only handles
	// first and fourth quadrant.
	(abs(theta) == (90 * (M_PI / 180))) ? theta = -theta : theta;
	
	// Basic SOHCAHTOA rules to find X,Y points. 
	returnXY.ptX = (nextStep * cos(theta));
	returnXY.ptY = (nextStep * sin(theta));

	// Places points in right quadrant, and in the right direction
	// from start to end.
	if (end.ptX < start.ptX)
	{
		returnXY.ptX = -returnXY.ptX;
		returnXY.ptY = -returnXY.ptY;
	}

		returnXY.ptX += start.ptX;
		returnXY.ptY += start.ptY;


	return returnXY;

}

void Line::setPoints(PointXY A, PointXY B)
{
	start = A;
	end = B;
}