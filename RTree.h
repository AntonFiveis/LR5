#pragma once
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
class Node {
public:
	vector<Node*> v;
	Node();
	Node(Rect);
};
class RTree
{
private:
	const int MAXNODESIZE = 3;
public:
	Node* root;
	RTree() {};
	RTree(vector<Rect>);
	void createTree(vector<Rect>);
	
};

