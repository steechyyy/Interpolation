#include <Geode/Geode.hpp>
#include "../headers/spline.hpp"
#include "../headers/point.hpp"

using namespace geode::prelude;

// costructor 2
Spline::Spline(const std::string& idNew)
	: id(idNew) {
}

/*
Spline::Spline(const std::string& idNew, std::vector<std::unique_ptr<Point>>& newPoints)
	: id(idNew), points(newPoints) {
}
might delete this
*/

//the best constructor
Spline::Spline(const std::string& idNew, const CCArray* objs)
	: id(idNew) {

	std::vector<std::unique_ptr<Point>> pointArr;
	CCObject* obj;

	//todo: sort all objects by x pos, evaluate 1st and last, normalize values
	CCARRAY_FOREACH(objs, obj) {
		GameObject* gameObject = static_cast<GameObject*>(obj);
		pointArr.push_back(
			std::make_unique<Point>(gameObject->getPositionX(), gameObject->getPositionY(), this)
		);
	}

	points = std::move(pointArr);
};

//clear the thing
void Spline::clear() {
	points.clear();
};

//bruh 2
Point* Spline::addPoint(Point&& p) {
	p.spline = this;
	points.push_back(std::make_unique<Point>(std::move(p)));
	return points.back().get();
};

// construct points from.. uh.. not a point
Point* Spline::addPoint(float t, float v) {
	points.push_back( std::make_unique<Point>(t, v, this) );
	return points.back().get();
};

bool Spline::removePointAtIndex(size_t index) {
	if (index >= points.size()) return false;
	points.erase(points.begin() + index);

	return true;
}

bool Spline::removePoint(Point* p) {
	auto it = std::find_if(points.begin(), points.end(),
		[p](const std::unique_ptr<Point>& up) { return up.get() == p; });
	if (it == points.end()) return false;

	points.erase(it);
	return true;

}

// hacks the us navy
Point* Spline::getPointAtIndex(size_t index) {
	if (index < points.size()) {
		return points[index].get();
	}
	
	return nullptr;
};

// gets iD
const std::string& Spline::getId() const {
	return id;
};

// bruh
const std::vector<std::unique_ptr<Point>>& Spline::getPoints() const {
	return points;
};