#include "Place.h"

Place::Place(string name, string Type, string subType, Rect r):
	name(name),Type(Type),subType(subType), coord(r){}

Rect::Rect(double lo, double la, double w = 0, double h = 0):
latitude(la),longitude(lo),width(w),height(h){}