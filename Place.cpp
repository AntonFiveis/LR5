#include "Place.h"

Place::Place(Rect r,string name="", string Type="", string subType=""):
	name(name),Type(Type),subType(subType), coord(r){}

Rect::Rect(double la, double lo, double w , double h ):
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
	rect = rect + node->getRect();
}

Rect operator+(Rect rect,Rect n_rect)
{
	
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
	return rect;
}
