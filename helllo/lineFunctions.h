#pragma once
#ifndef LINEFUNCTIONS
#define LINEFUNCTIONS

#include "point.h"
#include <math.h>

class lineFunctions
{
	public:
	
	/***TO GET THE INTERSECTION BETWEEN TWO LINES Im sure they are intersected***/
	void intersect(point a , point b , point c, point d , point &res)
	{
		/*if the first line parallel to the Y-AXIS*/
		if ( fabs( b.x - a.x ) < EPS )
		{
			float m2 = (d.y - c.y)/(d.x - c.x);
			float b2 = c.y - m2*c.x;

			float intersection_Y = m2 * a.x  + b2;// which is same as y2 - slope * x2
			res = point(round(a.x) ,round(intersection_Y));
			
			return;
		}


		/*if the second line parallel to the Y-AXIS*/

		if ( fabs( d.x - c.x ) < EPS )
		{
			float m1 = (b.y - a.y) / (b.x-a.x);
			float b1 = a.y - m1*a.x;

			float intersection_Y = m1 * c.x + b1;
			res = point(round(c.x),round(intersection_Y));

			return;

		}

		/**make the equation of the two line**/

		float m1 = (b.y - a.y)/(b.x - a.x);
		float m2 = (d.y - c.y)/(d.x - c.x);
		
		float b1 = a.y - m1 * a.x;
		float b2 = c.y - m2 * c.x;

        float intersection_X = (b2 - b1) / (m1 - m2);
        float intersection_Y = m1 * intersection_X + b1;

		res = point(round(intersection_X),round(intersection_Y));
		
	}

	/**To the nummber trimmed to nearest thousands term**/
	float round(float no)
	{
		int x = int(no);
		float diff = no - x;
		int y = diff*10000;
		return x + (y*1.0/10000.0);
	}

	/***TO GET THE PERBEDICULAR LINE TO A LINE CCW****/
	void perbedicular(point a , point b , point &mid , point &per)
	{

		float diff_Y = b.y - a.y;
		float diff_X = b.x - a.x;

		float perp_diff_Y = diff_X;
		float perp_diff_X = diff_Y*-1;

		per = point(mid.x + perp_diff_X , mid.y + perp_diff_Y);
	}

	/***TO GET THE MIDPOINT OF A LINE***/
	void midpoint(point a,point b,point &c)
	{
		c =  point((a.x + b.x)/2 ,(a.y + b.y)/2 );

	}

	/**TO know if the point on the left of the LINE or not**/
	bool ccw(point a,point b,point c)
	{
		float diff_x1 = b.x - a.x ;
		float diff_y1 = b.y - a.y ;

		diff_y1*=-1;

		float diff_x2 = c.x - a.x ;
		float diff_y2 = c.y - a.y ;

		return (diff_x1*diff_y2 + diff_x2*diff_y1 > EPS);

	}

	double Distance(point p1,point p2)
	{
		double x=p2.x-p1.x;
		x*=x;
		double y=p2.y-p1.y;
		y*=y;
		return sqrt(x+y);
	}
	
};

#endif