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
// Purpose: Contains some much needed structures //
//			so i just put it in a file to easily include.//
////
// //
// //
// Revision History //
// 05/19/2017 Jesse Schmidt //
// - Original Version //
// //
//************************************************************************//
#ifndef ROBOT_H
#define ROBOT_H
#define _USE_MATH_DEFINES
#include <math.h>
#include <strstream>
#include <string>
#include <iomanip>


enum Units { Rad, Deg };

struct Angles
{
	double angleOne;
	double angleTwo;
};

struct PointXY
{
	double ptX;
	double ptY;
	double ptZ;
};

template <class NumReturn>
NumReturn roundf(NumReturn fltPt, int pos = 0)
{
	strstream temp;
	temp << fixed << setprecision(pos) << fltPt;
	return atof(temp.str());
}

template <class RadDeg>
RadDeg unitsTo(Units mode, RadDeg convert)
{
	if (mode = Deg)
		return (convert * 180 / M_PI);

	else
		return (convert / 180 / M_PI);
}

#endif