#include <Geode/Geode.hpp>
#include "spline.hpp"
#include "InteractableGraphPoint.hpp"

using namespace geode::prelude;

// costructor 2
Spline::Spline(std::string_view idNew)
	: id(idNew) {
}

/*
Spline::Spline(const std::string& idNew, std::vector<std::unique_ptr<Point>>& newPoints)
	: id(idNew), points(newPoints) {
}
might delete this
*/

//the best constructor
Spline::Spline(std::string_view idNew, CCArray* objs)
	: id(idNew) {

	std::vector<InteractableGraphPoint*> pointArr;

	//todo: sort all objects by x pos, evaluate 1st and last, normalize values
	for (auto v : CCArrayExt<GameObject*>(objs)) {
		pointArr.push_back(InteractableGraphPoint::create("smallDot.png", this));
	}

	points = pointArr;
};

//clear the thing
void Spline::clear() {
	points.clear();
};

//bruh 2
InteractableGraphPoint* Spline::addPoint(InteractableGraphPoint* p) {
	p->setSpline(this);
	points.push_back(p);
	return points.back();
};

// construct points from.. uh.. not a point
InteractableGraphPoint* Spline::addPoint(float t, float v) {
	auto p = InteractableGraphPoint::create("smallDot.png", this);
	p->setValue(v);
	p->setTime(t);
	points.push_back(p);

	return points.back();
};

bool Spline::removePointAtIndex(size_t index) {
	if (index >= points.size()) return false;
	points.erase(points.begin() + index);

	return true;
}

bool Spline::removePoint(InteractableGraphPoint* p) {
	auto it = std::find_if(points.begin(), points.end(),
		[p](const std::unique_ptr<InteractableGraphPoint>& up) { return up.get() == p; });
	if (it == points.end()) return false;

	points.erase(it);
	return true;

}

// hacks the us navy
InteractableGraphPoint* Spline::getPointAtIndex(size_t index) {
	if (index < points.size()) {
		return points[index];
	}

	
	return nullptr;
};

// gets iD
std::string_view Spline::getId() const {
	return id;
};

// bruh
const std::vector<InteractableGraphPoint*> Spline::getPoints() const {
	return points;
};