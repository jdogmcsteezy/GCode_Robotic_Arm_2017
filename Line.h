
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