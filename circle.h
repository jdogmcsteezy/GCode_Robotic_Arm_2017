/* JESSE SCHMIDT 5/25/17 */
#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>
#include "Robots.h"
/*  CIRCLE CLASS
 * Class used to hold properties of a circle and compute other 
 * desired information about a cirlce based on paramters and
 * private data.
 */
class Circle
{
private:
	double radius;
	PointXY center;

public:
	/* Constructor
	 * @param double - radius of circle object
	 * @param PointXY struct - center of circle
	 */
	Circle(double radius = 1, PointXY center = { 0 });
	/* setRadius
	 * Mutator for radius.
	 * @param double - radius to assign circle.
	 */
	void setRadius(double radius);
	/* setCenter
	 * Mutator for center.
	 * @param PointXY struct - center point to assign circle.
	 */
	void setCenter(PointXY center);
	/* getRadius
	 * Accessor for circle radius.
	 * @return double - circle radius.
	 */
	double getRadius();
	/* getArea
	 * Computes area of instance or area of a desired circle. 
	 * If no paramater is detected default is used to indicate the 
	 * use of the instance radius.
	 * @param double - Radius of area to compute or default indicated instance area.
	 * @return double - circle radius.
	 */
	double getArea(double radius = 0);
	/* getCircum
	* Computes circumfrence of instance or circumfrence of a desired circle.
	* If no paramater is detected default is used to indicate the
	* use of the instance radius.
	* @param double - Radius of area to compute or default indicated instance area.
	* @return double - circle circumfrence.
	*/
	double getCircum(double radius = 0);
	/* getAnglePt
	 * Returns the angle of a pt from 0-2pi measured relative to
	 * to the origins x axis.
	 * @param PointXY struct - point to calculate angle of.
	 * @return double - Angle in radians 0-2pi.
	 */
	double getAnglePt(PointXY point);
	/* getAngleSteps
	 * Is used to determine how many partitians can be made of a circles outline
	 * with a desired resolution.
	 * @param double - Resoulution or length of each sector to be devided.
	 * @param radius - Radius of circle that to be computer upon. If default function will
	 *				   instance radius.
	 * @return double - Number of sectors that can be made.
	 */
	double getAngleSteps(double resolution, double radius = 0);
	/* getPoint
	 * Allows a user to input a desirex angle and radius of a circle and will return
	 * a point on the circumfrence of that circle. Default center will be origin.
	 * @param double - Angle used int calculation.
	 * @param radius - Radius to be used in calculation. If default is function will use instance
	 *				   radius.
	 * @return PointXY struct - Desired point.
	 */
	PointXY getPoint(double angle, double radius = 0);
	/* getPoint OVERLOAD
	 * Allows a user to input a desirex angle and radius of a circle and will return
	 * a point on the circumfrence of that circle.
 	 * @param double - Angle used int calculation.
	 * @param radius - Radius to be used in calculation.
	 * @param PointXY struct - Center of desired circle.
	 * @return PointXY struct - Desired point.
	 */
	PointXY getPoint(double angle, double radius, PointXY center);
};
#endif