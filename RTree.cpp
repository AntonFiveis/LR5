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
			splitToTwo(new_children[i]);
		}
	}
}

vector<Node*> RTree::splitHorizontal(Node* node) {
	auto children = node->getChildren();
	node->clearChildren();
	double mid_height = node->getRect().latitude + node->getRect().height / 2;
	Rect rect((node->getRect().longitude),(node->getRect().latitude));
	vector<Node*> nodes(2);
	nodes[0] = new Node(rect);
	nodes[1] = new Node(Rect(node->getRect().longitude,mid_height));
	for (auto i : children) {
		if ((rect + (i->getRect())).height < mid_height) {
			nodes[0]->addChild(i);
		}
		else {
			nodes[1]->addChild(i);
		}
	}
	return nodes;
}


vector<Node*> RTree::splitVertical(Node* node) {
	auto children = node->getChildren();
	node->clearChildren();
	double mid_width = node->getRect().longitude + node->getRect().width / 2;
	Rect rect(node->getRect().longitude, node->getRect().latitude);
	vector<Node*> nodes(2);
	nodes[0] = new Node(rect);
	nodes[1] = new Node(Rect(mid_width, node->getRect().latitude));
	for (auto i : children) {
		if ((rect + (i->getRect())).width < mid_width) {
			nodes[0]->addChild(i);
		}
		else {
			nodes[1]->addChild(i);
		}
	}
	return nodes;
}