#pragma once
#ifndef VORONOI
#define VORONOI

#include <map>
#include "point.h"
#include "lineFunctions.h"
#include <vector>

using namespace std;

class voronoi : lineFunctions
{
	void modify_polygon(vector<point> inp_polygon , point a , point b , vector<point>& res_polygon)
	{
		
		res_polygon.clear();
		for (int i=0 ; i<inp_polygon.size() ; ++i)
		{
			int j = (i+1) % inp_polygon.size() ;
			bool left_sided1 = lineFunctions::ccw( a , b ,inp_polygon[i]);
			bool left_sided2 = lineFunctions::ccw( a , b ,inp_polygon[j]);

			if (left_sided1) res_polygon.push_back(inp_polygon[i]);

			if( (left_sided1 && !left_sided2) || (!left_sided1 && left_sided2))
			{
				point intersect ;
				lineFunctions::intersect(a,b,inp_polygon[i],inp_polygon[j],intersect);
				res_polygon.push_back(intersect);
			}


		}
	}

	void vor(vector<point> obstacles,vector<point> boundaries,vector<vector<point> >& result)
	{
		result.clear();
		for (int i=0 ; i<obstacles.size() ; ++i)
		{
			result.push_back(boundaries);
			for (int j=0 ; j<obstacles.size() ; ++j)
			{
				if ( j == i ) continue;
				point mp , perp;
				
				lineFunctions::midpoint(obstacles[i],obstacles[j],mp);
				lineFunctions::perbedicular(obstacles[i],obstacles[j],mp,perp);

				vector<point> modified;

				modify_polygon(result.back() , mp , perp , modified);

				result.back() = modified;

			}
		}
	}

	bool found(point a , vector<point> v)
	{
		for (int i=0 ; i<v.size() ; ++i)
			if( a == v[i]) return true;
		return false;
	}

	void get_unique_line(vector<vector<point> > polygons,map<point,vector<point>>& res)
	{
		res.clear();
		map<point,vector<point>>::iterator it;
		map<point,vector<point>>::iterator it2;


		for (int i = 0 ; i < polygons.size() ; ++i)
		{
			for (int j = 0 ; j < polygons[i].size() ; ++j)
			{
				int k = (j+1) % polygons[i].size();
				point a(polygons[i][j].x , polygons[i][j].y);
				point b(polygons[i][k].x , polygons[i][k].y);

				it = res.find(a);
				it2 = res.find(b);

				if ( it != res.end() )
				{
					if(found(b,it->second)) continue;
					it->second.push_back(b);
				}
				else
				{
					vector<point> v;
					v.push_back(b);
					res[a] = v;
				}
				if ( it2 != res.end() )
				{
					if(found(a,it2->second)) continue;
					
					it2->second.push_back(a);
				}

				else
				{
					vector<point> v;
					v.push_back(a);
					res[b] = v;
				}
			}
		}
	}

public:

	void run( vector<point> obstacles, vector<point> bound, map<point,vector<point>>& res )
	{
		vector<vector<point> > polygons;

		vor(obstacles ,bound, polygons);
		

		get_unique_line(polygons,res);
	
	}

};
#endif