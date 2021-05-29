#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class rtree 
{
public:
	double x1, y1, x2, y2;
	rtree* northeast, * northwest, * southeast, * southwest;
	vector<point> points;

	void makeTree(ifstream input);
};

class point
{
public:
	double x, y;
	string type, subtype, name, adress;

	point(double x1, double y1, string typ, string styp, string nam, string adr) : x(x1), y(y1) , type(typ), subtype(styp), name(nam), adress(adr){};
};