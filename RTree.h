#pragma once
#include <vector>
using std::vector;
class RTree
{
private:
	const int MAXNODESIZE = 3;
public:
	class Node {
	public:
		vector<Node*> v;
		Node();
		
	};
};

