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
//			of a line from starting point to 
//  		ending point.//
// //
// //
// Revision History //
// 05/19/2017 Jesse Schmidt //
// - Original Version //
// //
//************************************************************************//
#ifndef LINE_H
#define LINE_H
#include "Robots.h"
#include <cmath>

class Line
{
private:
	PointXY start;
	PointXY end;

public:	
	Line();
	Line(PointXY const A , PointXY const B);
	PointXY getNextPt(const double nextStep);
	double getDistance();
	double getTheta();
	void setPoints(PointXY A, PointXY B);

};

#endif