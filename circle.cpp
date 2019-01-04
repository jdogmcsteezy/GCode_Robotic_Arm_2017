
#include "circle.h"
//
//Constructor
//	Takes arguments of double and struct PointXY
//	to instantiate the objects radius and center
//	variables.
//
Circle::Circle(double radius, PointXY center)
{
	this->radius = radius;
	this->center = center;
}

//SETRADIUS
//	Takes argument of double and assigns it to 
//	class private variable radius.
void Circle::setRadius(double radius)
{
	this->radius = radius;
}

//SETCENTER
//	Takes argument of PointXY  and assigns it to
//	class private variable center
void Circle::setCenter(PointXY center)
{
	this->center = center;
}

//GETRADIUS
//	Returns double of radius.
double Circle::getRadius()
{
	return radius;
}

//GETAREA
//	Returns the area of a this object by default
//	or returns area of a circle with radius of
//	argument double.
double Circle::getArea(double radius)
{
	if (radius == 0)
		return (M_PI * pow(this->radius, 2.0));

	else
		return (M_PI * pow(radius, 2.0));
}

//GETCIRCUM
//	Returns the circumfrence of a this object by default
//	or returns circumfrence of a circle with radius of 
//	argument double.
double Circle::getCircum(double radius)
{
	if (radius == 0)
		return (2 * M_PI * this->radius);

	else 
		return (2 * M_PI * radius);
}

//GETANGLEPT
//	Returns a double of angle in radians, of argument PointXY
//	with respect to the orgin. Return double will be 
//	between 0 and 2*M_PI.
double Circle::getAnglePt(PointXY point)
{
	double angle = atan((point.ptY - center.ptY) / (point.ptX - center.ptX)); //grab angle from point

	if ((point.ptX - center.ptX) < 0) // if that point is in 2 or 3 Q then it will either
	{								  // add or subtract from 180
			return M_PI + angle;
	}

	else  //if not and its in the 4 Q then we will substract from 360
	{
		if ((point.ptY - center.ptY) < 0)
			return (2 * M_PI) + angle;

		else //or just return the angle because its in the 1st Q
			return angle;
	}

}

//GETANGLESTEPS
//	Returns an angle resolution by takeing arguments double 
//	of wanted resolution and double radius of circle to 
//	return a double of the angle resolutions in radians.
double Circle::getAngleSteps(double resolution, double radius)
{
	double circumfrence = getCircum(radius);
	return ((2 * M_PI) / (circumfrence / resolution));
}

//GETPOINT
//	Returns a PointXY with respect to arguments double
//	angle and instantiated radius and center by default. 
//	A second argument can be used for different double radius.
PointXY Circle::getPoint(double angle, double radius)
{
	PointXY returnPt = { 0 };
	
	if (radius == 0)
		radius = this->radius;

	returnPt.ptX = (radius * cos(angle)) + center.ptX; //just uses angle input to find the next pt
	returnPt.ptY = (radius * sin(angle)) + center.ptY;

	return returnPt;
}

//GETPOINT
//	Returns a PointXY with respect to arguments double
//	angle, double radius, and PointXY center.
PointXY Circle::getPoint(double angle, double radius, PointXY center)
{
	PointXY returnPt;

	returnPt.ptX = (radius * cos(angle)) + center.ptX;
	returnPt.ptY = (radius * sin(angle)) + center.ptY;

	return returnPt;
}