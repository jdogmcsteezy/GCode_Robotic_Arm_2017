/* JESSE SCHMIDT 5/25/17 */
#ifndef LINE_H
#define LINE_H
#include "Robots.h"
#include <cmath>
/* Line Class
 * Simple line segmant class that stores starting and stopping
 * values of a line and computes all of the aspects 
 * of a line. Such as slope, length, and all points on
 * the line.
 */
class Line
{
private:
	PointXY start;
	PointXY end;

public:	
	/* Constructor 
	 * Initializes start and end points to (0,0)
	 */
	Line();
	/* Constructor OVERLOAD
	 *  Initializes start and end points.
	 * @param PointXY const - Point to start the line.
	 * @param PointXY const - Point to end the line.
	 */
	Line(PointXY const A , PointXY const B);
	/* setPoints
	 * Mutator for the start and end points of
	 * instance.
	 * @param PointXY const - Point to start the line.
	 * @param PointXY const - Point to end the line.
	 */
	void setPoints(PointXY A, PointXY B);
	/* getNextPt 
	 * Will use paramater to calculate a point that
	 * is on the line and a certain distance from the 
	 * start point.
	 * @param const double - Distance from the start of
	 *						 desired point.
	 * @return PointXY - The desired point struct.
	 */
	PointXY getNextPt(const double nextStep);
	/* getDistance
	 * Computed the length of line instance.
	 * @return double - length of line.
	 */
	double getDistance();
	/* getTheta
	 * Computes the slope of the line instance.
	 * @return double - Slope of line.
	 */
	double getTheta();
};

#endif