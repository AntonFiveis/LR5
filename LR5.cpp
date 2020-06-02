#include "RTree.h"
#include <iostream>
using namespace std;
int main()
{
	//cout << distance(Rect( -139.398,77.1539), Rect( -139.55,-77.1804 ));
	RTree rtree;
	rtree.createTreeFromFile("ukraine_poi.csv");
	vector<Place> places;
	//rtree.findInRadius(rtree.root, Rect(50, 30), 100000, places);
	for (auto i : places) {
		cout << i.getName() << endl;
	}
}