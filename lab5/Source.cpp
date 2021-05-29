#include "Header1.h"

using namespace std;

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

}