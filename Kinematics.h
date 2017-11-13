
#include<iostream>
#include<cMath>
#include"Robots.h"
#ifndef KINEMATICS_H
#define KINEMATICS_H
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
