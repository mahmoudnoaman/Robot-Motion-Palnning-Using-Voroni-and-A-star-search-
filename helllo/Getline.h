#pragma once
#ifndef GETLINE
#define GETLINE

#include<vector>
#include<math.h>
#include"point.h"
using namespace std;

class GetLine
{
private:
	//typedef pair<int,int> point;
	point p1,p2;
	double Diff_X,Diff_Y;
	double slope;
	double B_Y;
	vector<pair<float,float>> line;
	bool defined;
	bool positive_y;
	bool positive_x;
	bool slope_zero;
	float Y;

	void Slope()
	{
		defined=true;

		Diff_Y=p1.y-p2.y;
		Diff_X=p1.x-p2.x;
		if(Diff_Y==0) slope_zero=true;
		else slope_zero=false;
		if(Diff_X == 0) defined=false;
		if(defined)
			slope=Diff_Y/Diff_X;
		//else cout<<"Undefined Slope"<<endl; 
	}
	void Line_Equation()
	{
		if(defined)
			B_Y=p1.y-(p1.x*slope);
		//else cout<<"the equation will be : "<<"Y=X = "<<p1.x<<endl;
	}
	void Get_Points()
	{
		if(defined) //defined slope
		{
			if(slope_zero)
			{
				// p1-p2
				if(Diff_X <0) positive_x=false;
				else positive_x=true;
				for(int i=1;i<(abs(Diff_X));i++)
				{
					if(positive_x)
					{
						line.push_back(make_pair(p1.x-i,p1.y));
					}
					else
					{
						line.push_back(make_pair(p1.x+i,p1.y));
					}
				}
			}
			else
			{
				if(Diff_X <0) positive_x=false;
				else positive_x=true;
				for(int i=1;i<(abs(Diff_X));i++)
				{
					if(positive_x)
					{
						Y=(slope*(p1.x-i))+B_Y;
						line.push_back(make_pair(p1.x-i,Y));
					}
					else
					{
						Y=(slope*(p1.x+i))+B_Y;
						line.push_back(make_pair(p1.x+i,Y));
					}
				}
			}

		}
		else //undefined slope
		{
			if(Diff_Y <0) positive_y=false; //checking the sign to know the small Y
			else positive_y=true;
			for(int i=1;i<(abs(Diff_Y));i++)
			{
				if(positive_y) //if difference of Y is positive_y So.. the p1.y is bigger than of p2.y
				{
					line.push_back(make_pair(p1.x,p1.y-i));
				}
				else //if difference of Y is negative So.. the p2.y is bigger than of p1.y
				{
					line.push_back(make_pair(p1.x,p1.y+i));
				}

			}
		}

	}
public:
	
	void ComputeLine(point a,point b , vector<point>& points)
	{
		points.clear();
		points.push_back(a);
		p1.x=a.x; p1.y=a.y;
		p2.x=b.x; p2.y=b.y;
		Slope();
		Line_Equation();
		Get_Points();
		for(int i=0;i<line.size();i++)
		{
			points.push_back(point(line[i].first,line[i].second)); 
		}
		points.push_back(b);
	}
};
#endif