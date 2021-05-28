#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class rtree 
{
public:
	int x1, y1, x2, y2;
	rtree* northeast, * northwest, * southeast, * southwest;
	vector<pair<int, int>> points;

};
