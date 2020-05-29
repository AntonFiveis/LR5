#pragma once
#include <string>
using std::string;
struct Rect {
	double longitude;
	double latitude;
	double width;
	double height;
	Rect(double, double, double, double);
};
class Place
{
private:
	string name;
	string Type;
	string subType;
	Rect coord;
public:
	Place(string, string, string, Rect);
	string getName() { return name; };
	string getType() { return Type; };
	string getSubType() { return subType; };
	Rect getRect() { return coord; };
};