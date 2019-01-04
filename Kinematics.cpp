#include "Kinematics.h"

//CONSTRUCTOR
Kinematics::Kinematics()
{
	armOne = 1;
	armTwo = 1;
}

//CONSTRUCTOR(OVERLOAD)
//	Accepts double arm one and double arm two
//	in order to arm lengths of class.
Kinematics::Kinematics(const double armOne,const double armTwo)
{
	this->armOne = armOne;
	this->armTwo = armTwo;
}

//SETARMS
//	Assigns arm lengths of double arm one double
//	arm two to class object.
void Kinematics::setArms(const double armOne,const double armTwo)
{
	this->armOne = armOne;
	this->armTwo = armTwo;
}

//GETANGLE
//	Takes in arguments of PointXY of point and 
//	enumerated Units, returns a structer of Angles 
//	in units of enumeration(Deg, or Rad).
Angles Kinematics::getAngles(const PointXY point, const Units mode)
{
	Angles output;

	output.angleOne = acos((pow(point.ptX, 2) + pow(point.ptY, 2) 
		- pow(9, 2) - pow(9, 2)) / (2 * 9 * 9));

	output.angleTwo = ((asin((9 * sin(output.angleOne))
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