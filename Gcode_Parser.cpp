#include "Gcode_Parser.h"
Gcode_Parser::Gcode_Parser()
{
	this->ratio = 1;
	offset.ptX = 0;
	offset.ptY = 0;
	lineNumber = 0;
	NumberofLines = 0;
}
//CONSTRUCTOR
//	Takes in arguments char* of file to be opened, 
//	double of what to divide all command points by,
//	double of starting location of X point, 
//	double of starting location of Y point,
//	double of X offset, and double of Y offset.
Gcode_Parser::Gcode_Parser(char* fileName, double ratio, double initialX, double initialY, double Xoff, double Yoff)
{
	this->ratio = ratio;
	offset.ptX = Xoff;
	offset.ptY = Yoff;
	loadFile(fileName);
	lineNumber = 0;
	NumberofLines = 0;

}

//CONSTRUCTOR(OVERLOADED)
//	Only difference is it takes initial points
//	and offset points in the form of PointXY.
Gcode_Parser::Gcode_Parser(char* fileName, double ratio,PointXY intitialXY, PointXY offset)
{
	this->ratio = ratio;
	this->offset.ptX = offset.ptX;
	this->offset.ptY = offset.ptY;
	this->intitialXY.ptX = intitialXY.ptX;
	this->intitialXY.ptY = intitialXY.ptY;
	loadFile(fileName);
	lineNumber = 0;
	NumberofLines = 0;
}

Gcode_Parser::Gcode_Parser( double ratio, PointXY intitialXY, PointXY offset)
{
	this->ratio = ratio;
	this->offset.ptX = offset.ptX;
	this->offset.ptY = offset.ptY;
	this->intitialXY.ptX = intitialXY.ptX;
	this->intitialXY.ptY = intitialXY.ptY;
	lineNumber = 0;
	NumberofLines = 0;
}

//LOADFILE 
//	Takes argument char* of file to open
//	returns true if successful otherwise false.
bool Gcode_Parser::loadFile(const char* fileName)
{
	if (Gcode) //if a file is alread opened close it
		Gcode.close();

	Gcode.open(fileName); //then try and open the new file

	
	return (Gcode) ? true : false; // return ture if successful
}

//LOADFILE(OVERLOAD)
//	Simply returns true or false if
//	file is opened or not.
bool Gcode_Parser::loadFile()
{
	return (Gcode) ? true : false;
}

//GETNEXTLINE
//	Takes argument of a pointer to GCS structure to 
//	store G code extracted from a file.
//	Returns false if file is not properly loaded
//	or end of file has been reached.
bool Gcode_Parser::getNextLine(GCS *lineCode)
{
	if (NumberofLines == 0) //if line count is not set
	{
		while (getline(Gcode, buffer)) //count each line
			NumberofLines++;

		Gcode.clear(); //reset file cursor
		Gcode.seekg(0, std::ios::beg);
	}
	

	if (!Gcode)  //make sure file is open
		return false;

	if (lineNumber == 0)  //if no XY point has been read set XY points to initial
	{					  // to make sure to not send back a unwanted point.
		lineCode->X = intitialXY.ptX;
		lineCode->Y = intitialXY.ptY;
	}

	if (getline(Gcode, buffer))  //grab a new line if possible
	{
		int Gtemp;
		for (int index = 0; index < buffer.length(); index++) //increment through every char
		{
			if (buffer[index] == '(') //skip if there are comments
				while (buffer[index] != ')' && index < buffer.length())
					index++;

			switch (buffer[index]) //check for codes
			{
			case 'G': //if its a Gcode
				Gtemp = (atoi(&buffer[index + 1]));//grab the following integer

				if (Gtemp <= 4) //check if it a relevant int
				{
					lineCode->Gcommand = Gtemp;
					index += 2;
				}

				else //set the Gcommand to uninitialized value
				{
					lineCode->Gcommand = -1;
					getline(Gcode, buffer); //get another line
					index = 0;  //reset index of buffer
				}
				break;

			case 'X': // if X is found
 				lineCode->X = ((atof(&buffer[index + 1])) / ratio) + offset.ptX; //set it to GCS with offset
				index++; 
				lineNumber++; //lets object know we have found the first point and initial XY is no longer needed.
				break;

			case 'Y': // if Y is found
				lineCode->Y = ((atof(&buffer[index + 1])) / ratio) + offset.ptY; //set Y from gcs and grab the integer
				index++;
				break;

			case 'Z': // if Z is found
				lineCode->Z = (atof(&buffer[index + 1]));
				index++;
				break;

			case 'I': //if I is found
				lineCode->I = ((atof(&buffer[index + 1])) / ratio) + offset.ptX;
				index++;
				break;

			case 'J': //if J is found
				lineCode->J = ((atof(&buffer[index + 1])) / ratio) + offset.ptY;
				index++;
				break;
			}
		}
		return true;
	}

	else
		return false;
}


//SETOFFSET
//	Assigns arguments double X offset and double
//	Y offset to object to offset G code points.
void Gcode_Parser::setOffset(double Xoff, double Yoff)
{
	offset.ptX = Xoff;
	offset.ptY = Yoff;
}

//SETOFFSET(OVERLOAD)
//	Assigns arguments PointXY offset to object to 
//	offset G code points.
void Gcode_Parser::setOffset(PointXY offset)
{
	this->offset.ptX = offset.ptX;
	this->offset.ptY = offset.ptY;
}

//SETRATIO
//	Sets double ratio of g code to divide G code
//	file points by. For example if you have g code
//	file points in inches ratio would be set to 57.4 
//	in order to convert to milimeters.
void Gcode_Parser::setRatio(double units)
{
	this->ratio = units;
}

//DESTRUCTOR
Gcode_Parser::~Gcode_Parser()
{
	if (Gcode) //if file is open
		Gcode.close();
}