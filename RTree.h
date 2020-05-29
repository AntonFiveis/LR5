#pragma once
#include "Place.h"
#include <vector>
using std::vector;
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

