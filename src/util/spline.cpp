#include <Geode/Geode.hpp>
#include "../headers/spline.hpp"
#include "../headers/point.hpp"

using namespace geode::prelude;

Spline::Spline(const std::string& idNew)
	: id(idNew) {
}

Spline::Spline(const std::string& idNew, const std::vector<Point>& newPoints)
	: id(idNew), points(newPoints) {
}

Spline::Spline(const std::string& idNew, const CCArray* objs)
	: id(idNew) {
	
	std::vector<Point> pointArr;
	CCObject* obj;

	//todo: sort all objects by x pos, evaluate 1st and last, normalize values
	CCARRAY_FOREACH(objs, obj) {
		GameObject* gameObject = static_cast<GameObject*>(obj);
		pointArr.push_back(Point::Point(gameObject->getPositionX(), gameObject->getPositionY(), this));
	}

	points = pointArr;
}

void Spline::clear() {
	points.clear();
}

Point& Spline::addPoint(Point p) {
	points.push_back(p);
	return points.back();
}

Point& Spline::addPoint(float t, float v) {
	Point p(t, v, this);
	points.push_back(p);
	return points.back();
}

Point* Spline::getPointAtIndex(size_t index) {
	if (index < points.size()) {
		return &points[index];
	}
	return nullptr;
}

const std::string& Spline::getId() const {
	return id;
}

const std::vector<Point>& Spline::getPoints() const {
	return points;
}