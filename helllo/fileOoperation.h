#pragma once
#ifndef FILEOPERATION
#define FILEOPERATION 

#include<vector>
#include"point.h"
#include<map>
#include"voronoi.h"
#include"Astar.h"
#include<fstream>
#include<string>
#include"startEnd.h"
#include"Getline.h"


namespace project{
	
	
	void Run(vector<point> Obstacles,vector<point>  &Route)
	{
		//Returnpath.clear();
		point Source,Goal;
		bool Check = true;
		do
		{	
			Check = true;
			cout<<"Enter the Source Point : "<<endl;
			cin>>Source.x>>Source.y;
			cout<<"Enter The Goal Point : "<<endl;
			cin>>Goal.x>>Goal.y;
			for(int i=0;i<Obstacles.size();i++)
			{
				if(Source==Obstacles[i] || Goal==Obstacles[i])
					Check=false;
			}
		}while(!Check);
		voronoi v;
		Search s;
		Dist d;
		vector<point> bound;
		bound.clear();
		bound.push_back(point(0,300));
		bound.push_back(point(300,300));
		bound.push_back(point(300,0));
		bound.push_back(point(0,0));
		map<point,vector<point> > res;
		v.run(Obstacles,bound,res);
		double max1 = DBL_MAX;
		double max2 = DBL_MAX;
		pair<point,pair<point,point>> ns,ne;
		for (auto it = res.begin() ; it != res.end() ; ++it){
			point lineStart(it->first.x , it->first.y);
			for (int i=0 ; i <it->second.size() ; ++i){
				point lineEnd = it->second[i];
				point inter1,inter2;
				double dist1,dist2;
				d.compute(lineStart,lineEnd,Source,inter1,dist1);
				d.compute(lineStart,lineEnd,Goal,inter2,dist2);
				if ( dist1 < max1 ){
					ns.first = point(inter1.x,inter1.y);
					ns.second.first = point(lineStart.x,lineStart.y);
					ns.second.second = point(lineEnd.x,lineEnd.y);
					max1= dist1;
				}

				if ( dist2 < max2 ){
					ne.first = point(inter2.x,inter2.y);
					ne.second.first = point(lineStart.x,lineStart.y);
					ne.second.second = point(lineEnd.x,lineEnd.y);
					max2 = dist2;

				}
			}
		}
		map<point,vector<point> >::iterator it = res.find(ns.first);
		if ( it == res.end())
		{
			vector<point> vv;
			vv.push_back(ns.second.first);
			vv.push_back(ns.second.second);
			res[ns.first] = vv;
			res[ns.second.first].push_back(ns.first);
			for(int i = 0 ; i<res[ns.second.first].size() ; ++i){

				if( res[ns.second.first][i] == ns.second.second){
					res[ns.second.first].erase(res[ns.second.first].begin()+i);
					break;
				}
			}
			res[ns.second.second].push_back(ns.first);
			for(int i = 0 ; i<res[ns.second.second].size() ; ++i){

				if( res[ns.second.second][i] == ns.second.first){
					res[ns.second.second].erase(res[ns.second.second].begin()+i);
					break;
				}
			}
		}
		it = res.find(ne.first);
		if ( it == res.end())
		{
			vector<point> vv;
			vv.push_back(ne.second.first);
			vv.push_back(ne.second.second);
			res[ne.first] = vv;
			res[ne.second.first].push_back(ne.first);
			for(int i = 0 ; i<res[ne.second.first].size() ; ++i){

				if( res[ne.second.first][i] == ne.second.second ){

					res[ne.second.first].erase(res[ne.second.first].begin()+i);
					break;
				}
			}
			res[ne.second.second].push_back(ne.first);
			for(int i = 0 ; i<res[ne.second.second].size() ; ++i){

				if( res[ne.second.second][i] == ne.second.first){
					res[ne.second.second].erase(res[ne.second.second].begin()+i);
					break;
				}
			}
		}
		//vector<point> Route;
		
		double cost;
		GetLine ll;
		s.Run(res,ns.first,ne.first,Route,cost);
		/*for (int i=0 ; i<Route.size()-1 ;++i){
			vector<point> pointsofline;
			ll.ComputeLine(Route[i],Route[i+1],pointsofline);
			Returnpath.push_back(pointsofline);
		}*/
		
	}
	
	
}

#endif




