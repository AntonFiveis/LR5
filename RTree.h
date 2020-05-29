#pragma once
#include "Place.h"
#include <vector>
using std::vector;
struct Rect {
	double longitude;
	double latitude;
	double width;
	double height;
	Rect(double lo, double la, double w=0, double h=0) {
		longitude = lo;
		latitude = la;
		width = w;
		height = h;
	}
};

class RTree
{
private:
	const int MAXNODESIZE = 3;
public:
	Node* root;
	RTree():root(nullptr) {};
	void createTreeFromFile(string);
	void splitToTwo(Node*);
	vector<Node*> splitHorizontal(Node*);
	vector<Node*> splitVertical(Node*);
};

