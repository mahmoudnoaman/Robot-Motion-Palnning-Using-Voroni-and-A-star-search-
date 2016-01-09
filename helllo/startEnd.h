#pragma once
#ifndef STARTEND
#define STARTEND

#include<iostream>
#include<math.h>
#include<vector>
#include"point.h"
using namespace std;

class Dist
{
private:
	//typedef pair<int,int>point;
	double distance;
	point p1;
	point p2;
	double B2_Y;
	double B1_Y;
	point Start;
	point Intersect;
	double slope;
	double perpendicular;
	bool defined;
	bool slope_zero;
	void Slope()
	{
		defined=true;
		double Difference_Y=p2.y-p1.y;
		double Difference_X=p2.x-p1.x;
		if(Difference_Y==0) slope_zero=true;
		else slope_zero=false;
		if(Difference_X==0) defined=false;
		if (defined)
			slope=Difference_Y/Difference_X;
	}
	void Perpendicular()
	{
		if(defined && slope_zero==false)
				perpendicular=-1/slope;
		if(defined==false)
			perpendicular=0;
	}
	void Original_Line()
	{
		if(defined)
		B1_Y=p1.y-(slope*p1.x);
	}
	void Prep_Line()
	{
		if(slope_zero==false)
		B2_Y=Start.y-(perpendicular*Start.x);
	}
	void Intersect_point()
	{
		if(defined )
			
		{
			if  (slope_zero==false)
			{
		Intersect.x=(B2_Y-B1_Y)/(slope-perpendicular);
		Intersect.y=(slope*Intersect.x)+(B1_Y);
			}
			else
			{
				Intersect.x=Start.x;
				Intersect.y=p1.y;
			}
		}
		else if(defined==false)
		{
			Intersect.x=p1.x;
			Intersect.y=Start.y;
		}
	}

public:
	double D_point_Line()
	{
		double X;
		double Y;
		double D;
		X=(Intersect.x-Start.x);
		X*=X;
		Y=(Intersect.y-Start.y);
		Y*=Y;
		D=sqrt(X+Y);
		return D;
	}
	void Read_Point_Line(point start,point P1,point P2)
	{
		Start=start;
		p1=P1;
		p2=P2;
	}
	void compute(point a,point b,point c,point& intersect,double& dist)
	{
		p1.x=a.x; p1.y=a.y;
		p2.x=b.x; p2.y=b.y;
		Start.x=c.x;  Start.y=c.y;
		Slope();
		Perpendicular();
		Original_Line();
		Prep_Line();
		Intersect_point();
		intersect.x=Intersect.x;  intersect.y=Intersect.y;
		dist=D_point_Line();
	}
	
};
#endif