/* JESSE SCHMIDT 5/25/17 */
#ifndef RHINO_H
#define RHINO_H
#include <iostream>
#include <cMath>
#include <iomanip>
#include "tserial.h"
#include "Kinematics.h"
#include "Line.h"
#include "circle.h"

// Enumeration to simplify the identification of Rhino joint motors.
enum Motors{C = 67,
			D = 68,
			E = 69,
			F = 70,};


class Rhino
{
	private:
		// Instance to comunicate with Robot through 9600
		// baud serial port.
		Tserial Robot;
		// Used to calculate arm angles.
		Kinematics math;
		// Used to calculate line points from Gcode commands.
		Line line;
		// Used to calcualte circle points from Gcode commands.
		Circle circle;

		// Store angles current arm counts and next arm counts.
		Angles armCounts;
		Angles nextAngles;

		PointXY currentXY;

		const int Home = 750;

		double armOne;
		double armTwo;

		// Checks the status of limit switches.
		bool switchStatus(const Motors check);
		// Checks to see the status of a motor.
		int motorCount(const Motors check);
		// Converts angles to a motor tick counts.
		void toTicks(Angles &convert);
		// Abstracts away complications when trying to send
		// large movments to a motor. This is needed to not
		// overload the buffer.
		bool sendCommands(const Motors motor, int count);
	
	public:

		/* Constructor
		 * Initializes Rhino class with arm lengths and establishes
		 * serial communication between the control computers.
		 * @param char* - Name of desired com port to connect through.
		 * @param const double - Length of armOne.
		 * @param const double - Length of armTwo.
		 */
		Rhino(char* comPort,const double armOne,const double armTwo);
		/* home
		 * Is used when the robot needs to calibrate its position.
		 * When called it will direct to robot back to 90 degrees
		 * between the two arms. To do this it uses the detection of
		 * limit switches.
		 */
		 void home();
		 /* moveTo
		  * Completes the complicated computation that is needed to
		  * get the robot to move from its current location to a 
		  * desired location.
		  * @param const PointXY - The new desired location.
		  * @return bool - Returns true when done, unless the move is
		  *				   not possible.
		  */
		 bool moveTo(const PointXY &newPt);
		 /* moveTo_Line
		  * Utilizes the line class and moveTo function in order to 
		  * move alone a straight line using many increments.
		  * @param const PointXY - Desired end point for line to move along.
		  * @param double - The resolution in which you want the line to be drawn.
		  * @param bool - False if Robo was unable to draw line.
		  */
		 bool moveTo_Line(const PointXY &newPt, double resolution);
		 /* operator <<
		  * Helper function to make sending command to robot much easier
		  * @param char* const - C_string to send.
		  */
		 void operator << ( char* const ptr){Robot << ptr;};
};

#endif