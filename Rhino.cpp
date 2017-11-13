#include "Rhino.h"

Rhino::Rhino(char* comPort, const double armOne, const double armTwo)
{
	Robot.connect(comPort, 9600, spEVEN);
	math.setArms(armOne, armTwo);
	nextAngles = { 0, 0 };
	armCounts = { 0, 0 };
	currentXY = { 0, 0 };
	this->armOne = armOne;
	this->armTwo = armTwo;
}

bool Rhino::switchStatus(const Motors check)
{
	Sleep(15);
	char status;
	char mask = (pow(2, (check - 67)));
	Robot << 'I';
	Sleep(15);
	Robot >> status;
	status -= 32;
	
	return(status & mask);
	
}

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
	Sleep(15);

	Robot << status;

	Sleep(15);

	Robot >> reply;
	//return 0;

	return int(reply)- 32;
}

void Rhino::home()
{  
	
	while (switchStatus(E))
	{
		Robot << "E-5";
		while (!motorCount(E)){ ; }
	}
	
	while (switchStatus(D))
	{
		Robot << "D+5";
		while (motorCount(D)){ ; }
	}

	armCounts.angleOne = 750;
	armCounts.angleTwo = 750;

	currentXY.ptX = armOne;
	currentXY.ptY = armTwo;

}

bool Rhino::moveTo(const PointXY &newPt)
{
	nextAngles = math.getAngles(newPt, Deg);

	if (isnan(nextAngles.angleOne))
	{
		std::cout << "You asked for an INVALID Point!" << std::endl;
		return false;
	}


	std::cout << "Angles: " << nextAngles.angleOne << "  " << nextAngles.angleTwo << std::endl;

	toTicks(nextAngles);

	sendCommands(D, roundf((armCounts.angleTwo - nextAngles.angleTwo) + (nextAngles.angleOne - armCounts.angleOne)));
	sendCommands(E, roundf(nextAngles.angleTwo - armCounts.angleTwo));


	armCounts.angleOne = nextAngles.angleOne;
	armCounts.angleTwo = nextAngles.angleTwo;

	std::cout << "( " << newPt.ptX << ", " << newPt.ptY << ") : " << nextAngles.angleOne << "  " << nextAngles.angleTwo << std::endl;

	currentXY.ptX = newPt.ptX;
	currentXY.ptY = newPt.ptY;

	return true;
}



void Rhino::toTicks(Angles &convert)
{
	convert.angleOne = (convert.angleOne / .12);
	convert.angleTwo = (convert.angleTwo / .12);
}

bool Rhino::sendCommands(const Motors motor, int count)
{

	while (motorCount(D) > 0){ ; }
	char send[6] = { 0 };
	string command;
	switch (motor)
	{
	case C:
		//make sure to fix when we get to using this motor
		command += 'C';
		count > 0 ? command += '+' : command += '-';
		command += "50";
		count = abs(count);
		while (count >= 50)
		{
			std::cout << command.c_str() << endl;
			count -= 50;
			
			while (motorCount(C) > 50){ ; }
		}
		if (count < 50 && count > 0)
		{
			command.replace(2, 2, to_string(count));
			std::cout << command.c_str() << endl;
		}
		break;

	case D:
		command += 'D';
		count > 0 ? command += '-' : command += '+';
		command += "50";
		count = abs(count);
		while (count >= 50)
		{
			strcpy(send, command.c_str());
			Robot << send;
			std::cout << command.c_str() << endl;
			count -= 50;
			
			while (motorCount(D) > 50){;}
		}
		if (count < 50 && count > 0)
		{
			command.replace(2, 2, to_string(count));
			std::cout << command.c_str() << endl;
			strcpy(send, command.c_str());
			Robot << send;
		}
		
		break;
	case E:
		command += 'E';
		count > 0 ? command += '-' : command += '+';
		command += "50";
		count = abs(count);
		while (count >= 50)
		{
			strcpy(send, command.c_str());
			Robot << send;
			std::cout << command.c_str() << endl;
			count -= 50;
			
			while ( motorCount(E) > 50){ ; }
		}
		if (count < 50 && count > 0)
		{
			command.replace(2, 2, to_string(count));
			std::cout << command.c_str() << endl;
			strcpy(send, command.c_str());
			Robot << send;
		}

		break;
	}
	return true;
}

bool Rhino::moveTo_Line(const PointXY &newPt, double resolution)
{
	line.setPoints(currentXY, newPt);

	double distance = line.getDistance();

	for (double dist = resolution; dist <= distance; dist += resolution)
	{
		moveTo(line.getNextPt(dist));

		if ((distance - dist) <= resolution)
		{
			dist = distance;
			moveTo(line.getNextPt(dist));
		}
	}
	return true;
}