/* JESSE SCHMIDT 5/25/17 */
#include "circle.h"


Circle::Circle(double radius, PointXY center)
{
	this->radius = radius;
	this->center = center;
}

void Circle::setRadius(double radius)
{
	this->radius = radius;
}

void Circle::setCenter(PointXY center)
{
	this->center = center;
}

double Circle::getRadius()
{
	return radius;
}
double Circle::getArea(double radius)
{
	if (radius = 0)
		return (M_PI * pow(this->radius, 2.0));

	else
		return (M_PI * pow(radius, 2.0));
}

double Circle::getCircum(double radius)
{
	if (radius = 0)
		return (2 * M_PI * this->radius);

	else 
		return (2 * M_PI * radius);
}

double Circle::getAnglePt(PointXY point)
{
	double angle = atan((point.ptY - center.ptY) / (point.ptX - center.ptX));

	if ((point.ptX - center.ptX) < 0)
	{
			return M_PI + angle;
	}

	else
	{
		if ((point.ptY - center.ptY) < 0)
			return (2 * M_PI) + angle;

		else 
			return angle;
	}
}

double Circle::getAngleSteps(double resolution, double radius)
{
	double circumfrence = getCircum(radius);
	return ((2 * M_PI) / (circumfrence / resolution));
}
// getPoint if correct radius and center are located with in class
PointXY Circle::getPoint(double angle, double radius)
{
	PointXY returnPt;
	// If default is given use instance data.
	if (radius == 0)
		radius = this->radius;
	// Compute X,Y point and add center offset.
	returnPt.ptX = (radius * cos(angle)) + center.ptX;
	returnPt.ptY = (radius * sin(angle)) + center.ptY;

	return returnPt;
}
// getPoint if radius and center are not privately located within class
PointXY Circle::getPoint(double angle, double radius, PointXY center)
{
	PointXY returnPt;

	if (radius == 0)
		radius = this->radius;
	// Compute X,Y point and add center offset.
	returnPt.ptX = (radius * cos(angle)) + center.ptX;
	returnPt.ptY = (radius * sin(angle)) + center.ptY;

	return returnPt;
}