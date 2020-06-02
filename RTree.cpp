#include "RTree.h"
#include <fstream>
#include <cmath>
using namespace std;
const double PI = 3.1415;
const double rad = 6372795;
double distance(Rect point1, Rect point2) {
	double lat1 = point1.latitude * PI / 180;
	double lat2 = point2.latitude * PI / 180;
	double long1 = point1.longitude * PI / 180;
	double long2 = point2.longitude * PI / 180;
	double cl1 = cos(lat1);
	double cl2 = cos(lat2);
	double sl1 = sin(lat1);
	double sl2 = sin(lat2);
	double cdelta = cos(long2 - long1);
	double sdelta = sin(long2 - long1);
	double y = sqrt(pow(cl2 * sdelta, 2) + pow(cl1 * sl2 - sl1 * cl2 * cdelta, 2));
	double x = sl1 * sl2 + cl1 * cl2 * cdelta;
	return atan2(y, x) * rad;
}

bool colliseInRadius(Node* node, Rect point, double radius) {
	auto n_rect = node->getRect();
	
	if (point.latitude < n_rect.latitude) {
		if (point.longitude < n_rect.longitude) {
			if (distance(n_rect, point) < radius) {
				return true;
			}
		}
		else if (point.longitude <= n_rect.longitude + n_rect.width) {
			if (distance(Rect(n_rect.latitude, point.longitude), point) < radius) {
				return true;
			}
		}
		else {
			if (distance(Rect(n_rect.latitude, n_rect.longitude + n_rect.width), point) < radius) {
				return true;
			}
		}
	}

	else if (point.latitude < n_rect.latitude + n_rect.height) {
		if (point.longitude < n_rect.longitude) {
			if(distance(Rect(point.latitude, n_rect.longitude), point) < radius) {
				return true;
			}
		}
		else if ( point.longitude <= n_rect.longitude + n_rect.width) {
			return true;
		}
		else {
			if (distance(Rect(point.latitude, n_rect.longitude + n_rect.width), point) < radius) {
				return true;
			}
		}
	}
	else {
		if (point.longitude < n_rect.longitude) {
			if (distance(Rect(n_rect.latitude+n_rect.height, n_rect.longitude), point) < radius) {
				return true;
			}
		}
		else if (point.longitude <= n_rect.longitude + n_rect.width) {
			if (distance(Rect(n_rect.latitude + n_rect.height, point.longitude), point) < radius) {
				return true;
			}
		}
		else {
			if (distance(Rect(n_rect.latitude+n_rect.height, n_rect.longitude + n_rect.width), point) < radius) {
				return true;
			}
		}	
	}


	return false;
}

bool colliseWithRect(Node* node, Rect point, double a) {
	auto n_rect = node->getRect();
	if (point.latitude < n_rect.latitude) {
		if (point.longitude < n_rect.longitude) {
			if (distance(Rect(point.latitude, n_rect.longitude), point) < a / 2 && distance(Rect(n_rect.latitude, point.longitude), point) < a / 2) {
				return true;
			}
		}
		else if (point.longitude <= n_rect.longitude + n_rect.width) {
			if (distance(Rect(n_rect.latitude, point.longitude), point) < a/2) {
				return true;
			}
		}
		else {
			if (distance(Rect(point.latitude, n_rect.longitude + n_rect.width), point) < a/2&& distance(Rect(n_rect.latitude, point.longitude), point) < a / 2) {
				return true;
			}
		}
	}

	else if (point.latitude < n_rect.latitude + n_rect.height) {
		if (point.longitude < n_rect.longitude) {
			if (distance(Rect(point.latitude, n_rect.longitude), point) < a/2) {
				return true;
			}
		}
		else if (point.longitude <= n_rect.longitude + n_rect.width) {
			return true;
		}
		else {
			if (distance(Rect(point.latitude, n_rect.longitude + n_rect.width), point) < a/2) {
				return true;
			}
		}
	}
	else {
		if (point.longitude < n_rect.longitude) {
			if (distance(Rect(n_rect.latitude + n_rect.height, point.longitude), point) < a/2&& distance(Rect(point.latitude,n_rect.longitude+n_rect.width), point) < a / 2) {
				return true;
			}
		}
		else if (point.longitude <= n_rect.longitude + n_rect.width) {
			if (distance(Rect(n_rect.latitude + n_rect.height, point.longitude), point) < a) {
				return true;
			}
		}
		else {
			if (distance(Rect(point.latitude, n_rect.longitude + n_rect.width), point) < a / 2 && distance(Rect(n_rect.latitude+n_rect.height, point.longitude), point) < a / 2) {
				return true;
			}
		}
	}


	return false;
}

double strToDouble(string s) {
	double ans = 0;
	int i;
	for ( i = 0; i < s.size() && s[i] != ','; i++) {
		ans *= 10;
		ans += s[i] - '0';
	}
	int x = 1;
	for (i = i + 1; i < s.size(); i++) {
		ans += (s[i] - '0') / pow(10, x);
		x++;
	}
	return ans;
}

void RTree::createTreeFromFile(string file_name)
{
	ifstream iFile(file_name);
	
	while (!iFile.eof()) {
		double lo, la;
		string slo, sla;
		string Type, subType, adress;
		getline(iFile, sla, ';');
		if (sla.length() == 0) break;
		la = strToDouble(sla);
		getline(iFile, slo, ';');

		lo = strToDouble(slo);
		getline(iFile,Type, ';');

		getline(iFile,subType, ';');
		
		getline(iFile, adress);
		Node* node = new Node(Place(Rect(la,lo), Type, subType, adress));
		if (root == nullptr) {
			root = new Node(Rect(la,lo));
		}
		root->addChild(node);
	}
	splitToTwo(root);
}

void RTree::splitToTwo(Node* node)
{
	try {
		if (root && node->getChildrenNumb() > MAXNODESIZE) {
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
	catch (exception e) {
		int x = 0;
	}
}

vector<Node*> RTree::splitHorizontal(Node* node) {
	auto children = node->getChildren();
	node->clearChildren();
	double mid_height = node->getRect().latitude + node->getRect().height / 2;
	Rect rect((node->getRect().latitude),(node->getRect().longitude));
	vector<Node*> nodes(2);
	nodes[0] = new Node(rect);
	nodes[1] = new Node(Rect(mid_height,node->getRect().longitude));
	for (auto i : children) {
		if ((rect + (i->getRect())).height < mid_height - node->getRect().latitude) {
			nodes[0]->addChild(i);
		}
		else {
			nodes[1]->addChild(i);
		}
	}
	if (nodes[0]->getChildrenNumb() == 0)
		delete nodes[0];
	if (nodes[1]->getChildrenNumb() == 0)
		delete nodes[1];
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
		if ((rect + (i->getRect())).width < mid_width- node->getRect().longitude) {
			nodes[0]->addChild(i);
		}
		else {
			nodes[1]->addChild(i);
		}
	}
	if (nodes[0]->getChildrenNumb() == 0) {
		delete nodes[0];
	}
	if (nodes[1]->getChildrenNumb() == 0)
		delete nodes[1];
	return nodes;
}

void RTree::findInRadius(Node* node,Rect point, double radius,vector<Place>& places)
{
	if (colliseInRadius(node, point,radius)) {
		if (node->place == nullptr) {
			auto children = node->getChildren();
			for (auto i : children) {
				findInRadius(i, point, radius, places);
			}
		}
		else {
			places.push_back(*(node->place));
		}
	}
}

void RTree::findInRect(Node* node, Rect point, double a, vector<Place>& places) {

	if (colliseWithRect(node, point, a)) {
		if (node->place == nullptr) {
			auto children = node->getChildren();
			for (auto i : children) {
				findInRadius(i, point, a, places);
			}
		}
		else {
			places.push_back(*(node->place));
		}
	}
}