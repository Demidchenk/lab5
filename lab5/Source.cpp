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
    if (p.x > (x1+x2)/2 && p.y > (y1+y2)/2) northeast->insert(p);
    if (p.x < (x1 + x2) / 2 && p.y > (y1 + y2) / 2) northwest->insert(p);
    if (p.x > (x1 + x2) / 2 && p.y < (y1 + y2) / 2) southeast->insert(p);
    if (p.x < (x1 + x2) / 2 && p.y < (y1 + y2) / 2) southwest->insert(p);
    return;
}

void rtree::makeTree(string fileName)
{
    ifstream input(fileName);
	double lon, lat;
	string typ, styp, nam, adr, temp;
    getline(input, temp);
    do
    {
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

        point p(lat, lon, typ, styp, nam, adr);
        this->insert(p);
        getline(input, temp);
    } while (!input.eof() && temp != "");
}

void rtree::findPoints(double x, double y, double radius, string type, vector<point> &result)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (distance(x, y, points[i].x, points[i].y) <= radius && points[i].type == type)
            result.push_back(points[i]);
    }
    if (isDivided)
    {
        if (distance(x, y, (x1 + x2) / 2, (y1 + y2) / 2) < radius)
        {
            northeast->findPoints(x, y, radius, type, result);
            northwest->findPoints(x, y, radius, type, result);
            southeast->findPoints(x, y, radius, type, result);
            southwest->findPoints(x, y, radius, type, result);
            return;
        }
        if (pointInRectangle(x, y, northeast->x1, northeast->y1, northeast->x2, northeast->y2))
        {
            northeast->findPoints(x, y, radius, type, result);
            if (y-(radius/111.2) < southeast->y2) southeast->findPoints(x, y, radius, type, result);
            if (x-(radius/111.2/cos(y*M_PI/180)) < northwest->x2) northwest->findPoints(x, y, radius, type, result);
            return;
        }
        if (pointInRectangle(x, y, southeast->x1, southeast->y1, southeast->x2, southeast->y2))
        {
            southeast->findPoints(x, y, radius, type, result);
            if (y + (radius / 111.2) > northeast->y1) northeast->findPoints(x, y, radius, type, result);
            if (x - (radius / 111.2 / cos(y * M_PI / 180)) < southwest->x2) southwest->findPoints(x, y, radius, type, result);
            return;
        }
        if (pointInRectangle(x, y, northwest->x1, northwest->y1, northwest->x2, northwest->y2))
        {
            northwest->findPoints(x, y, radius, type, result);
            if (y - (radius / 111.2) < southwest->y2) southwest->findPoints(x, y, radius, type, result);
            if (x + (radius / 111.2 / cos(y * M_PI / 180)) > northeast->x1) northeast->findPoints(x, y, radius, type, result);
            return;
        }
        if (pointInRectangle(x, y, southwest->x1, southwest->y1, southwest->x2, southwest->y2))
        {
            southwest->findPoints(x, y, radius, type, result);
            if (y + (radius / 111.2) > northwest->y1) northwest->findPoints(x, y, radius, type, result);
            if (x + (radius / 111.2 / cos(y * M_PI / 180)) > southeast->x1) southeast->findPoints(x, y, radius, type, result);
            return;
        }
    }
}

double distance(double x1, double y1, double x2, double y2)
{
    double R = 6371;
    double lat1 = x1 * M_PI / 180;
    double lat2 = x2 * M_PI / 180;
    double dlat = (x2 - x1) * M_PI / 180;
    double dlon = (y2 - y1) * M_PI / 180;
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}

bool pointInRectangle(double pointx, double pointy, double x1, double y1, double x2, double y2)
{
    if (pointx >= x1 && pointx <= x2 && pointy >= y1 && pointy <= y2) return true;
    return false;
}