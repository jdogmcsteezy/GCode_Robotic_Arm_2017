#include "Rhino.h"

//CONSTRUCTOR
//	Takes argument of char* of comport to 
//	connect through serial port. Second
//	argument of Rotation set the direction
//	Rhino must rotate to go on to surface.
Rhino::Rhino(const char* comPort, Rotation OnRotate)
{
	connectError = Robot.connect(comPort, 9600, spEVEN);
	math.setArms(9, 9);
	nextAngles = { 0, 0 };
	armCounts = { 0, 0 };
	currentXY = { 0, 0, 0 };
	this->armOne = 9;
	this->armTwo = 9;
	this->OnRotate = OnRotate;

}


//SWITCHSTATUS 
//	Takes argument of enumurated type holding
//	motors. Returns true if motor switch status
//	is not set.
bool Rhino::switchStatus(const Motors check)
{
	Sleep(25);
	char status;
	char mask = (pow(2, (check - 67)));
	Robot << 'I';
	Sleep(25);
	Robot >> status;
	status -= 32;
	
	return(status & mask);
	
}

//MOTORCOUNT
//	Takes argument of enumerated Motor
//	to check and returns int motor count .
int Rhino::motorCount(const Motors check)
{
	char reply;

	char status[] = { " ?"};

	switch (check)
	{
	case C:
		status[0] = C;
		break;
	case D:
		status[0] = D;
		break;
	case E:
		status[0] = E;
		break;

	default:
		return 0;
	}
	Sleep(25);

	Robot << status;

	Sleep(25);

	Robot >> reply;
	//return 0; //for testing

	return int(reply)- 32;
}

//HOME
//	Puts Rhino at home position.
void Rhino::home()
{  
	
	while (switchStatus(E))   //home E motor
	{
		Robot << "E-5";
		while (!motorCount(E)){ ; }
	}
	
	while (switchStatus(D))    // home D motor
	{
		Robot << "D+5";
		while (motorCount(D)){ ; }
	}

	armCounts.angleOne = 750;   //set home tick counts
	armCounts.angleTwo = 750;

	currentXY.ptX = armOne;      //set current position
	currentXY.ptY = armTwo;
	currentXY.ptZ = -1.0;
}

//MOVETO
//	Moves Rhino to PointXY newPt and
//	returns true when complete or false
//	if not capable.
bool Rhino::moveTo(const PointXY &newPt)
{
	nextAngles = math.getAngles(newPt, Deg);   //grab angles for new point
	
	if (isnan(nextAngles.angleOne))  //check if is not a number
	{
		return false;
	}

	if(newPt.ptZ != currentXY.ptZ)     //move on or off if needed
	(newPt.ptZ >= 0) ? move_OnOff(0) : move_OnOff(1);

	toTicks(nextAngles);   //convert the angles to ticks /.12

	sendCommands(D, int(roundf((armCounts.angleTwo - nextAngles.angleTwo) + (nextAngles.angleOne - armCounts.angleOne))));  //send commands
	sendCommands(E, int(roundf((nextAngles.angleTwo - armCounts.angleTwo))));


	armCounts.angleOne = ((nextAngles.angleOne));   //set new tick counts
	armCounts.angleTwo = ((nextAngles.angleTwo));


	currentXY.ptX = (newPt.ptX);  //set new arm position
	currentXY.ptY = (newPt.ptY);

	return true;
}

//MOVETO_LINE
//	Moves rhino to PointXY newPt in a line
//	at the second argument double resolution.
bool Rhino::moveTo_Line(const PointXY &newPt, double resolution)
{
	line.setPoints(currentXY, newPt);  //initialize new pts in line object

	double distance = line.getDistance(); //grab length

	if (newPt.ptZ != currentXY.ptZ)  //move on or off if needed
	(newPt.ptZ >= 0) ? move_OnOff(0) : move_OnOff(1);

	for (double dist = resolution; dist <= distance; dist += resolution) //while length is less than total distance
	{
		moveTo(line.getNextPt(dist)); //move to next pt returned by line function
	}
	moveTo(line.getNextPt(distance));  //when broken out of loop move to last pt

	return true;
}

//MOVETO_ARC
//	Moves rhino to PointXY newPt, with PointXY
//	center, with double resolution, in enumerated
//	Rotation direction. Returns true when done or false
//	if not possible.
bool Rhino::moveTo_Arc(const PointXY &newPt, const PointXY &center, const double resolution, const Rotation rotate)
{
	PointXY nextPoint = { 0 }; //holds each individual point in arc
	circle.setCenter(center);  //set circle object center pt
	circle.setRadius(sqrt(pow((center.ptX - currentXY.ptX), 2) + pow((center.ptY - currentXY.ptY), 2))); //set circle object radius
	
	double currentAngle = circle.getAnglePt(currentXY);  //establish current position in cirlce
	double lastAngle = circle.getAnglePt(newPt);  //establish end position in circle
	double angleResolution = circle.getAngleSteps(resolution); //get the angle increment for wanted resolution

	if (newPt.ptZ != currentXY.ptZ)  //move on or off if needed
	(newPt.ptZ >= 0) ? move_OnOff(0) : move_OnOff(1);

	if (rotate == 1) //if arc is in CCW direction
	{
		if (lastAngle <= currentAngle)  //add 360 of last angle is less than first
			lastAngle += (2 * M_PI);
		
		for (double angleStep = angleResolution; (currentAngle + angleStep) < lastAngle; angleStep += angleResolution)
		{
			nextPoint = circle.getPoint(currentAngle + angleStep); //get next point with incrimented angle arg
			nextPoint.ptZ = currentXY.ptZ;
			moveTo(nextPoint); //move to that point

		}
		nextPoint = circle.getPoint(lastAngle); //when you break out just move to last point
		nextPoint.ptZ = currentXY.ptZ;
		moveTo(nextPoint);

	}

	else if (rotate == 0) //if CW direction
	{
		if (lastAngle >= currentAngle) //if last angle is greater add 360 to current
			currentAngle += (2 * M_PI);

		for (double angleStep = angleResolution; (currentAngle - angleStep) > lastAngle; angleStep += angleResolution)
		{
			nextPoint = circle.getPoint(currentAngle - angleStep); //get next pt from angle incrementor
			nextPoint.ptZ = currentXY.ptZ;
			moveTo(nextPoint); // go to that pt

		}
		nextPoint = circle.getPoint(lastAngle); 
		nextPoint.ptZ = currentXY.ptZ;
		moveTo(nextPoint); //when you break out just go this point
	}
	return true;
}

//MOVE_ONOFF
//	Takes argument of int 0 or 1,
//	1 if you want the robot on the surface
//	or 0 if you want the robot off the surface.
//	Return true when done.
bool Rhino::move_OnOff(int OnOff)
{
	if (OnOff == 1) //if you want it on
	{
		if (currentXY.ptZ == -1.0) //its already on
		{
			return true;
		}

		else //its not on
		{
			if (OnRotate == CCW) //CCW direction to ON
				Robot << "F+20";
			

			else  //CW direction to ON
				Robot << "F-20";

		}
		currentXY.ptZ = -1.0; //set new z value
		return true;
	}
	else // you want it off
	{
		if (currentXY.ptZ == 0.0) // but its already off
		{
			return true;
		}

		else // its not off yet
		{
			if (OnRotate == CCW)
				Robot << "F-20";

			else
				Robot << "F+20";
		}

		currentXY.ptZ = 0.0; //set new z value
		return true;
	}

}
//TOTICKS
//	Turns Angle structure from angles to
//	Rhino ticks.
void Rhino::toTicks(Angles &convert)
{
	convert.angleOne = (convert.angleOne / .12);
	convert.angleTwo = (convert.angleTwo / .12);


}

//SENDCOMMANDS
//	Sends appropriate commands to Rhino argument
//	Motor, and int count.
bool Rhino::sendCommands(const Motors motor, int count)
{
	while (motorCount(F) != 0){ ; } //make sure all motors are not moving
	while (motorCount(D) != 0){ ; }
	while (motorCount(E) != 0){ ; }
	char send[6] = { 0 }; //hold string
	string command;
	switch (motor)
	{

	case D: //for D motor
		command += 'D';
		count > 0 ? command += '-' : command += '+';
		command += "50";
		count = abs(count);
		while (count >= 50) //while units is greater that 50
		{
			strcpy(send, command.c_str());
			Robot << send; //send 50
			count -= 50;
			
			while (motorCount(D) > 0){;} //then wait until done
		}
		if (count < 50 && count > 0) //if less than 50
		{
			command.replace(2, 2, to_string(count));
			strcpy(send, command.c_str());
			Robot << send; //just sent that remaining count
		}
		
		break;
	case E:  // if E motor
		command += 'E'; 
		count > 0 ? command += '-' : command += '+';
		command += "50";
		count = abs(count);
		while (count >= 50)  //if count creater than 50
		{
			strcpy(send, command.c_str());
			Robot << send;  //go ahead and send 50
			count -= 50;
			
			while ( motorCount(E) > 0){ ; } // then wait for it to be done
		}
		if (count < 50 && count > 0)  // if less than 50
		{
			command.replace(2, 2, to_string(count));
			strncpy(send, command.c_str(), command.length());
			Robot << send;  // go ahead and send count
		}

		break;
	}
	return true;
}


