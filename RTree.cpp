#include "RTree.h"
#include <fstream>
using namespace std;
void RTree::createTreeFromFile(string file_name)
{
	ifstream iFile(file_name);
	
}

void RTree::splitToTwo(Node* node)
{
	if (node->getChildrenNumb() > MAXNODESIZE) {
		auto children = node->getChildren();
		node->clearChildren();
		auto n_rect = node->getRect();
		vector<Node*> new_children;
		if (n_rect.height > n_rect.width) {
			new_children = splitHorizontal(node);
		}
		else {
			new_children = splitVertical(node);
		}
		for (int i = 0; i < new_children.size(); i++) {
			node->addChild(new_children[i]);
		}
	}
}
