#pragma once
#ifndef POINT
#define POINT

#include<iostream>
using namespace std;

#define EPS 1e-3

class point
{
public:
	float x;
	float y;

	point() {}

	point(float a , float b) { x = a ; y = b ; }

	bool operator ==(const point &p)const { return fabs(p.x-this->x)<EPS && fabs(p.y-this->y)<EPS; }

	bool operator !=(const point &p)const { return (p.x!=this->x || p.y!=this->y); }

	bool operator <(const point &p) const{
		if(fabs(x - p.x) <= EPS)
			return y < p.y;
		return x < p.x;
	}

	bool operator > (const point& p) const{
		if(fabs(x - p.x) <= EPS)
			return y > p.y;
		return x > p.x;
	}
};
#endif