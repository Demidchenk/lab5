#include "Header1.h"

using namespace std;

void rtree::insert(point p)
{
    if (p.x < x1 || p.x > x2 || p.y < y1 || p.y > y2)
        return;

    if (points.size() < capacity)
    {
        points.push_back(p);
        return;
    }

    if (!isDivided)
    {
        northeast = new rtree((x1 + x2) / 2, (y1 + y2) / 2, x2, y2);
        northwest = new rtree(x1, (y1 + y2) / 2, (x1 + x2) / 2, y2);
        southeast = new rtree((x1 + x2) / 2, y1, x2, (y1 + y2) / 2);
        southwest = new rtree(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2);
        isDivided = true;
    }
    northeast->insert(p);
    northwest->insert(p);
    southeast->insert(p);
    southwest->insert(p);
    return;
}

void rtree::makeTree(ifstream input)
{
	double lon, lat;
	string typ, styp, nam, adr, temp;
	getline(input, temp);

    while (temp.find(',') != -1)
        temp[temp.find(',')] = '.';
    lat = stod(temp.substr(0, temp.find(';')));
    temp = temp.substr(temp.find(';') + 1);
    lon = stod(temp.substr(0, temp.find(';')));
    temp = temp.substr(temp.find(';') + 1);
    typ = temp.substr(0, temp.find(';'));
    temp = temp.substr(temp.find(';') + 1);
    styp = temp.substr(0, temp.find(';'));
    temp = temp.substr(temp.find(';') + 1);
    nam = temp.substr(0, temp.find(';'));
    temp = temp.substr(temp.find(';') + 1);
    adr = temp.substr(0, temp.find(';'));

    point p(lon, lat, typ, styp, nam, adr);
    this->insert(p);
}

double distance(double x1, double x2, double y1, double y2)
{
    double R = 6371e3;
    double lat1 = x1 * M_PI / 180;
    double lat2 = x2 * M_PI / 180;
    double dlat = (x2 - x1) * M_PI / 180;
    double dlon = (y2 - y1) * M_PI / 180;
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}