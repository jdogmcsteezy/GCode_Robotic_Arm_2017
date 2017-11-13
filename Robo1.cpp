
#include<iostream>
#include"Rhino.h"
#include"Line.h"
#include"circle.h"

using namespace std;


int main()
{	

//____________________________Circle Testing_________________________________
	//Circle Test;

	//PointXY XY = { 0, -5};
	//cout << "Angle: " << Test.getAnglePt(XY) * (180/M_PI) << endl;
	//
	//PointXY check = Test.getPoint(Test.getAnglePt(XY), 5);

	//cout << " X: " << roundf(check.ptX, 14) << endl;
	//cout << " Y: " << roundf(check.ptY, 14) << endl;

	//_________________________________________________________________________




	//cout << "Distance: " << test.getDistance() << endl;

	//cout << "Theta: " << test.getTheta() * (180 / M_PI) << endl;

	//_______________Line Test________________________________________________
	Rhino Test("COM3", 9, 9);
	PointXY XY1 = { 5, 5 };
	PointXY XY2 = { 15, 5 };
	PointXY XY3 = { 10, 10 };
	PointXY XY4 = { -1, -6 };

	Test.home();

	system("pause");
	Line test(XY1, XY2);
	PointXY check;
	double resolution = .5;

	Test.moveTo(XY1);
	Test.moveTo_Line(XY2, .1);
	Test.moveTo_Line(XY3, .1);
	Test.moveTo_Line(XY1, .1);
	



	//for (double i = 0; i <= test.getDistance(); i += resolution)
	//{
	//	check = test.getNextPt(i);

	//	cout << "\nX : " << check.ptX << endl;
	//	cout << "Y : " << check.ptY << endl;

	//	if ((test.getDistance() - i) <= resolution)
	//	{
	//		i = test.getDistance();
	//		check = test.getNextPt(i);

	//		cout << "\nX : " << check.ptX << endl;
	//		cout << "Y : " << check.ptY << endl;
	//	}

	//}

	//system("pause");
	//test.setPoints(XY2, XY3);

	//for (double i = 0; i <= test.getDistance(); i += resolution)
	//{
	//	check = test.getNextPt(i);

	//	cout << "\nX : " << check.ptX << endl;
	//	cout << "Y : " << check.ptY << endl;

	//	if ((test.getDistance() - i) <= resolution)
	//	{
	//		i = test.getDistance();
	//		check = test.getNextPt(i);

	//		cout << "\nX : " << check.ptX << endl;
	//		cout << "Y : " << check.ptY << endl;
	//	}

	//}

	//system("pause");
	//test.setPoints(XY3, XY1);

	//for (double i = 0; i <= test.getDistance(); i += resolution)
	//{
	//	check = test.getNextPt(i);

	//	cout << "\nX : " << check.ptX << endl;
	//	cout << "Y : " << check.ptY << endl;

	//	if ((test.getDistance() - i) <= resolution)
	//	{
	//		i = test.getDistance();
	//		check = test.getNextPt(i);

	//		cout << "\nX : " << check.ptX << endl;
	//		cout << "Y : " << check.ptY << endl;
	//	}

	//}
	//______________________________________________________________________
	//for (; XY.ptY <= 16; XY.ptX--, XY.ptY++)
	//{
	//	Angles AB = test.getAngles(XY, Deg);
	//	cout << "( " << XY.ptX << ", " << XY.ptY << ") : " << AB.angleOne << "  " << AB.angleTwo << endl;
	////}
	/*Test.sendCommands(D, (750 - 710) + 1112 - 750);
	Test.sendCommands(E, 710-750);*/
	

	//Test.home();

	//while (1)
	//{
	//	system("pause");
	//	cin >> XY.ptX >> XY.ptY;
	//	Test.moveTo(XY);
	//}
	//system("pause");

	//Test.moveTo(XY);

	//system("pause");

	//XY.ptX = 5;
	//XY.ptY = 5;

	//Test.moveTo(XY);



	
	system("pause");
	//switchStatus(D, &robot);


	/*
	char test1[20];
	

	robot.connect("com1", 9600, spEVEN);
	 
    while(1)
    {
	  robot.sendChar('d');
      cin >> test1;
	  robot << test1;
    }*/
	return 0;
}