#include "Header1.h"

using namespace std;

int main()
{
    rtree tree(0, 0, 90, 60);
    tree.makeTree("ukraine_poi.csv");

    double lat, lon, n;
    cin >> lat >> lon >> n;

}
