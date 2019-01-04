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
// Purpose: Be able to parse out a Gcode file //
//			and return the points and commands//
// //
// //
// Revision History //
// 05/19/2017 Jesse Schmidt //
// - Original Version //
// //
//************************************************************************//
#ifndef GCODE_PARSER_H
#define GCODE_PARSER_H

#include <fstream>
#include <string>
#include "Robots.h"

struct GCS //structure to be used by user to pass in by reference
{		   // for return values
	int Gcommand = -1;
	double X, Y, Z;
	double I, J;
};

class Gcode_Parser
{
private:
	std::ifstream Gcode; // holds file handle
	PointXY offset;
	PointXY intitialXY;
	double ratio;
	std::string buffer; //for input from file
	int lineNumber;
	int NumberofLines;


public:
	Gcode_Parser();
	Gcode_Parser(char* fileName, double ratio, double initialX, double initialY, double Xoff, double Yoff);
	Gcode_Parser(char* fileName, double ratio, PointXY intitialXY = { 0 }, PointXY offset = { 0 });
	Gcode_Parser(double ratio, PointXY intitialXY, PointXY offset);
	bool loadFile(const char* fileName);
	bool loadFile();
	int getLineNumbers() { return NumberofLines; };
	bool getNextLine(GCS *lineCode);
	void setOffset(double Xoff, double Yoff);
	void setOffset(PointXY offset = { 0 });
	void setRatio(double oneTo);
	PointXY getOffset() { return offset; }
	double getRatio() { return ratio; }
	~Gcode_Parser();
};

#endif