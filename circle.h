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
// Purpose: Be able to calculate all aspects //
//			of a circle.						//
// //
// //
// Revision History //
// 05/19/2017 Jesse Schmidt //
// - Original Version //
// //
//************************************************************************//
#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>
#include "Robots.h"

class Circle
{
private:
	double radius;
	PointXY center;

public:
	Circle(double radius = 1, PointXY center = { 0 });
	void setRadius(double radius);
	void setCenter(PointXY center);
	double getRadius();
	double getArea(double radius = 0); 
	double getCircum(double radius = 0);
	double getAnglePt(PointXY point);
	double getAngleSteps(double resolution, double radius = 0);
	PointXY getPoint(double angle, double radius = 0);
	PointXY getPoint(double angle, double radius, PointXY center);
};
#endif