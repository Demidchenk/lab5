#include "Header1.h"

using namespace std;

int main()
{
    rtree tree(0, 0, 90, 60);
    tree.makeTree("ukraine_poi.csv");
    cout << "Finished building\n";

    double lat, lon, n;
    string type;
    cin >> lat >> lon >> n >> type;

    vector<point> result;
    tree.findPoints(lat, lon, n, type, result);

    cout << "We found next entities in the sector:\n";
    for (int i = 0; i < result.size(); i++)
        cout << i + 1 << ". " << result[i].subtype << ", " << result[i].name << ", " << result[i].adress << endl;
}
