#include "Kinematics.h"

Kinematics::Kinematics()
{
	armOne = 0;
	armTwo = 0;
}

Kinematics::Kinematics(const double armOne,const double armTwo)
{
	this->armOne = armOne;
	this->armTwo = armTwo;
}

void Kinematics::setArms(const double armOne,const double armTwo)
{
	this->armOne = armOne;
	this->armTwo = armTwo;
}



Angles Kinematics::getAngles(const PointXY point, const Units mode)
{
	Angles output;

	output.angleOne = acos((pow(point.ptX, 2) + pow(point.ptY, 2) 
		- pow(armOne, 2) - pow(armTwo, 2)) / (2 * armOne*armTwo));

	output.angleTwo = ((asin((armTwo * sin(output.angleOne)) 
		/ sqrt(pow(point.ptX, 2) + pow(point.ptY, 2))))
		+ atan(point.ptY / point.ptX));

	if (mode == Deg)
	{
		output.angleOne = unitsTo(Deg, output.angleOne);
		output.angleTwo = unitsTo(Deg, output.angleTwo);
		return output;
	}
	
	else
		return output;
}