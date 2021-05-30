#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class point
{
public:
	double x, y;
	string type, subtype, name, adress;

	point(double x1, double y1, string typ, string styp, string nam, string adr) : x(x1), y(y1), type(typ), subtype(styp), name(nam), adress(adr) {};
};

class rtree 
{
public:
	double x1, y1, x2, y2;
	rtree* northeast, * northwest, * southeast, * southwest;
	vector<point> points;
	int capacity = 4;
	bool isDivided = false;

	rtree(double X1, double Y1, double X2, double Y2) : x1(X1), y1(Y1), x2(X2), y2(Y2) {};

	void insert(point p);
	void makeTree(string fileName);
	void findPoints(double x, double y, double radius, string type, vector<point> result);
};

double distance(double x1, double x2, double y1, double y2);
bool pointInRectangle(double pointx, double pointy, double x1, double y1, double x2, double y2);