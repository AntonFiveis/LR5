#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;
struct Rect {
	double longitude;
	double latitude;
	double width;
	double height;
	Rect() { longitude = latitude = width = height = 0; }
	Rect(double, double, double w =0, double h=0);
};
Rect operator+(Rect,Rect);
class Place
{
private:
	string name;
	string Type;
	string subType;
	Rect coord;
public:
	Place(Rect,string, string, string);
	string getName() { return name; };
	string getType() { return Type; };
	string getSubType() { return subType; };
	Rect getRect() { return coord; };
};

class Node {
private:
	Rect rect;
	vector<Node*> children;
public:
	Place* place;
	Node();
	Node(Rect);
	Node(Place);
	void addChild(Node*);
	vector<Node*> getChildren() { return children; }
	void clearChildren() { children.clear(); }
	Rect getRect() { return rect; }
	int getChildrenNumb() { return children.size(); }
	~Node() {
		delete place;
	}
};