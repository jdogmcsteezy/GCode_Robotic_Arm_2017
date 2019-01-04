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
// Purpose: Calculate angles of obleque triangles //
//			with specified side lenghts			//
// //
// //
// Revision History //
// 05/19/2017 Jesse Schmidt //
// - Original Version //
// //
//************************************************************************//
#ifndef KINEMATICS_H
#define KINEMATICS_H
#include<cMath>
#include"Robots.h"
#include "Robots.h"

class Kinematics
{

private:
	double armOne;
	double armTwo;

public:
	Kinematics();

	Kinematics(const double armOne, const double armTwo);

	void setArms(const double armOne, const double armTwo);
	

	Angles getAngles(const PointXY point, const Units mode = Rad);

	~Kinematics(){}
};

#endif
