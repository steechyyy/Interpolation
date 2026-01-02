#include <Geode/Geode.hpp>
#include <spline.hpp>

using namespace geode::prelude;

std::vector<Spline> splines;

Spline::Spline(const std::string idNew, const std::vector<Point*> newPoints) 
	: id(idNew), points(newPoints) {}

Spline::Spline(const std::string idNew) 
	: id(idNew) {}


void Spline::clear() {
	for (auto p : points) delete p;
	points.clear();
};

Point* Spline::addPoint(Point* p) {
	points.push_back(p);
	return p;
};

Point* Spline::getPointAtIndex(size_t index) {
	if (index >= 0 && index < points.size()) {
		return points[index];
	};

	return nullptr;
};

const std::string Spline::getId() {
	return id;
};

const std::vector<Point*>& Spline::getPoints() const {
	return points;
};



