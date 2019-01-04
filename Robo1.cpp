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
// Purpose: Draws images with rhino robot //
//			from Gcode file //
// //
// Effects: //
// The expected usage is: //
// 1. Specify comport number and file name//
// 2. Watch robot draw pictures           //
// 3. Be sadly done with COM-11//
// //
// Revision History //
// 05/19/2017 Jesse Schmidt //
// - Original Version //
// //
//************************************************************************//
#include<fstream>
#include<iostream>
#include"Rhino.h"
#include"Line.h"
#include"circle.h"
#include"Gcode_Parser.h"

using namespace std;

int main()
{
	string buffer;    //holds input
	PointXY current = { 0 };  //holds the current location for arc center
	PointXY XYZ = { 9, 9 ,-1 }; // holds innitial point, then holds next pt to sent to Rhino
	PointXY offSet = { 0, 0 }; // if you need and offset
	PointXY ArcCenter = { 0 }; //hold arc center to send to Rhino
	GCS Gcode;					//parser structure defined in Gcode_Parser
	Gcode_Parser parser( 1, XYZ, offSet); // parser object
	string comPort =  "COM ";		//comport string for connecting to comport with rhoino
	int GcodeLines;					// hold number of line in gcode file
	

	cout << " What ComPort are you using?\n ";  //Input for comport number
	getline(cin, buffer);
	comPort[3] = buffer[0];
	Rhino Test(comPort.c_str(), CCW); // create Rhino object

	while (!Test.isConnected()) //test the serial connection
	{
		cout << " Wrong ComPort, Try Again\n ";
		getline(cin, buffer);
		comPort[3] = buffer[0];
		Test.connect(comPort.c_str());  // try to connect again
	}

	do
	{
		cout << " What is the file name you would like to read G code from?\n ";
		getline(cin, buffer);
		parser.loadFile(buffer.c_str());  // load the file into parser object

	} while (!parser.loadFile());  //keep trying if load file failed

	do  // sets the direction the rhino must roatate to become in contact with the board
	{
		cout << " What direction does the robot rotate to make contact with the white-board?" << endl;
		cout << " 1. Clockwise" << endl;
		cout << " 2. Counter Clockwise\n ";
		getline(cin, buffer);
	} while (atoi(&buffer[0]) != 1 && atoi(&buffer[0]) != 2);

	(atoi(&buffer[0]) == 1) ? Test.setRotate(CW) : Test.setRotate(CCW); //set on rotate direction

	Test.home(); // homes the robot

	int linecount = 1;

	while (parser.getNextLine(&Gcode)) // get the next line
	{
		cout << "\r Progress:" << linecount << "/" << parser.getLineNumbers() << flush; // print the progress of program
		current = Test.getCurrentPt(); //grab the curent point

		XYZ.ptX = Gcode.X;  //grab values from GCS and store into point structures to pass to move func.
		XYZ.ptY = Gcode.Y;
		XYZ.ptZ = Gcode.Z;

		ArcCenter.ptX = Gcode.I + current.ptX; //because the center is an offset of the current position
		ArcCenter.ptY = Gcode.J + current.ptY;

		if (Gcode.Gcommand == 1) //move in line
			Test.moveTo_Line(XYZ, .1);

		else if (Gcode.Gcommand == 0) // move fast and jagged
			Test.moveTo(XYZ);

		else if (Gcode.Gcommand == 2)  //move in cw arc with .1in increment
			Test.moveTo_Arc(XYZ, ArcCenter, .1, CW);

		else if (Gcode.Gcommand == 3) //move in ccw arc with .1in increment
			Test.moveTo_Arc(XYZ, ArcCenter, .1, CCW);

		linecount++;
	}
	cout << " -DONE!-" << endl;

	do
	{
		cout << "Would you line to return to the initial position?\n [Y\N] : ";  // ask to move back to home position
		getline(cin, buffer);

	} while (toupper(buffer[0]) != 'Y' && toupper(buffer[0]) != 'N');

	if (toupper(buffer[0]) == 'Y')
	{
		XYZ.ptX = 9;
		XYZ.ptY = 9;
		XYZ.ptZ = -1;

		Test.moveTo(XYZ); // move to home position
	}
	cout << " Thanks for using Jesse Schimdt robot program COM_SCI 11!" << endl;
}