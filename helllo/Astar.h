#pragma once
#ifndef ASTAR
#define ASTAR

#include<queue>
#include<map>
#include<vector>
#include"lineFunctions.h"

class Search
{
private:
	map<point,bool>Visited;
	map<point,double>Cost_table;
	map<point,point>Path;
	map<point,vector<pair<double,point>>>MP;
	map<point,vector<pair<double,point>>>::iterator it2;
	lineFunctions l;
public:
	void Run(map<point,vector<point>>M , point Start , point Goal , vector<point>& Route ,double& totalCost)
	{
	
		map<point,vector<point>>::iterator it1;
		vector<pair<double,point>>V;
		for(it1 =M.begin();it1!=M.end();++it1)
		{
			point A(it1->first.x,it1->first.y);
			V.clear();
			MP[A]=V;
			for(int i=0;i<it1->second.size();i++)
			{
				double distance = l.Distance(A,it1->second[i]);
				MP[A].push_back(make_pair(distance,it1->second[i]));
			}
			Visited[it1->first]=false;
			Cost_table[it1->first]=DBL_MAX;
		}
		A_Star(Start,Goal);
		totalCost = Cost_table[Goal];
		while(Path[Goal].x != -1 && Path[Goal].y != -1 ){

			Route.push_back(Goal);
			Goal = point(Path[Goal].x , Path[Goal].y);
		}
		Route.push_back(Start);
		reverse(Route.begin(),Route.end());
	}
	void A_Star(point Source,point Goal)
	{
		priority_queue<pair<double,point>,vector<pair<double,point>>,greater<pair<double,point>>>Q;
		Cost_table[Source]=0;
		Path[Source]=point(-1,-1);
		double Currentf = l.Distance(Source,Goal);
		Q.push(make_pair(Currentf,Source));
		while ( !Q.empty())
		{
			point Current(Q.top().second.x,Q.top().second.y);
			float CurrentCost = Cost_table[Current];
			Q.pop();
			Visited[Current]= true;
			if ( Current == Goal) return;

			for(int i=0;i<MP[Current].size();i++){
				point Adjacent(MP[Current][i].second.x,MP[Current][i].second.y);
				double cost = MP[Current][i].first; 
				if(!Visited[Adjacent] && cost + CurrentCost < Cost_table [Adjacent]){
					Path[Adjacent] = Current;
					Cost_table[Adjacent] = cost + CurrentCost;
					double h = l.Distance(Adjacent,Goal);
					Q.push(make_pair(h + Cost_table[Adjacent] ,Adjacent));
				}

			}
		}
	}
};
#endif