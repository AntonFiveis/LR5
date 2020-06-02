#include "RTree.h"
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	if (argc != 5) {
		return 1;
	}
	string db;
	double la, lo;
	double radius;
	for (int i = 1; i < 5; i++) {
		if (argv[i][2] == 'd') {
			
			for (int j = 5; argv[i][j] != '\0'; j++) {
				db += argv[i][j];
			}
		}
		else if (argv[i][3] == 'a') {
			string sla;
			for (int j = 6; j < argv[i][j] != '\0'; j++) {
				sla += argv[i][j];
			}
			la = stod(sla);
		}
		else if (argv[i][3] == 'o') {
			string slo;
			for (int j = 7; j < argv[i][j] != '\0'; j++) {
				slo += argv[i][j];
			}
			lo = stod(slo);
		}
		else if (argv[i][2] == 's') {
			string sr;
			for (int j = 7; j < argv[i][j] != '\0'; j++) {
				sr += argv[i][j];
			}
			radius = stod(sr);
		}
		
	}
	//cout << distance(Rect( -139.398,77.1539), Rect( -139.55,-77.1804 ));
	RTree rtree;
	rtree.createTreeFromFile(db);
	vector<Place> places;
	rtree.findInRadius(rtree.root, Rect(la, lo), radius*1000, places);
	for (auto i : places) {
		cout <<i.getType() <<' '<<i.getName() << endl;
	}
}