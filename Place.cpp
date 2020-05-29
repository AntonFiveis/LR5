#include "Place.h"

Place::Place(Rect r,string name="", string Type="", string subType=""):
	name(name),Type(Type),subType(subType), coord(r){}

Rect::Rect(double lo, double la, double w = 0, double h = 0):
latitude(la),longitude(lo),width(w),height(h){}

Node::Node():rect(0,0)
{
	place = nullptr;
}

Node::Node(Rect rect):rect(rect),place(nullptr)
{}

Node::Node(Place pl):rect(pl.getRect())
{
	place = new Place(pl);
}

void Node::addChild(Node* node)
{
	children.push_back(node);
	Rect n_rect = node->getRect();
	if (rect.longitude > n_rect.longitude) {
		rect.width = rect.longitude + rect.width - n_rect.longitude;
		rect.longitude = n_rect.longitude;
	}
	if (rect.longitude + rect.width < n_rect.longitude + n_rect.width) {
		rect.width = n_rect.longitude + n_rect.width - rect.longitude;
	}
	if (rect.latitude > n_rect.latitude) {
		rect.height = rect.latitude + rect.height - n_rect.latitude;
		rect.latitude = n_rect.latitude;
	}
	if (rect.latitude + rect.height < n_rect.latitude + n_rect.height) {
		rect.height = n_rect.latitude + n_rect.height - rect.latitude;
	}
}
