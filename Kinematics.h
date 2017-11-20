/* JESSE SCHMIDT 5/25/17 */
#include<iostream>
#include<cMath>
#include"Robots.h"
#ifndef KINEMATICS_H
#define KINEMATICS_H
/* Kinematics Class
 * Class used for simple two arm kinematic equations.
 * It uses the length of two arms stores as private variable
 * to then calculate the needed angles between the first arm
 * relative to the x axis and the second arm relative to 
 * to the first. All using the law of sines and cosines.
 */
class Kinematics
{

private:
	double armOne;
	double armTwo;

public:
	/* Constructor 
	 * Sets arm lengths to 0.
	 */
	Kinematics();
	/* Constructor OVERLOADED
	 * Sets arm lengths to to paramter lengths.
	 * @param const double - First arm length.
	 * @param const double - Second arm lenth.
	 */
	Kinematics(const double armOne, const double armTwo);
	/* setArms
	 * Mutator for arm lengths.
	 * @param const double - First arm length.
	 * @param const double - Second arm lenth.
	 */
	void setArms(const double armOne, const double armTwo);
	/* getAngles
	 * Uses the point given relative to the origin to calculate
	 * the two desired angles that the arms must be at in order
	 * to get to the desired cartesian coordinate. The function 
	 * used the laws of sines and cosines 
	 * @param const PointXY - Desired end point of arms.
	 * @param cont Units Enumeration - An enumeration that allows 
	 *						the user to choose degrees or radians.
	 * @return Angles - A struct containing both angles.
	 */
	Angles getAngles(const PointXY point, const Units mode = Rad);
	/* Destuctor */
	~Kinematics(){}
};

#endif
