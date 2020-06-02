#pragma once
#include "Place.h"
#include <vector>
using std::vector;
class RTree
{
private:
	const int MAXNODESIZE = 4;
public:
	Node* root;
	RTree():root(nullptr) {};
	void createTreeFromFile(string);
	void splitToTwo(Node*);
	vector<Node*> splitHorizontal(Node*);
	vector<Node*> splitVertical(Node*);
	void findInRadius(Node*,Rect, double, vector<Place>&);
	void findInRect(Node*,Rect,double,vector<Place>&);
};

double distance(Rect point1, Rect point2);

