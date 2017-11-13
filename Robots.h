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