#include <common.hpp>
#include <SplineManager.hpp>

using namespace geode::prelude;

Spline* SplineManager::newSpline(const std::string& id) {
	if (getSplineById(id) != nullptr) return nullptr;

	auto s = std::make_unique<Spline>(id);
	splines.push_back(std::move(s));
	return splines.back().get();
};

/*
Spline* SplineManager::newSpline(const std::string& id, const std::vector<Point>& points) {
	auto s = std::make_unique<Spline>(id, points);
	splines.push_back(std::move(s));
	return splines.back().get();
};
*/

Spline* SplineManager::newSpline(const std::string& id, const CCArray* objs) {
	if (getSplineById(id) != nullptr) return nullptr;

	auto s = std::make_unique<Spline>(id, objs);
	splines.push_back(std::move(s));
	return splines.back().get();
};

Spline* SplineManager::addSpline(Spline&& s) {
	if (getSplineById(s.getId()) != nullptr) return nullptr;

	auto ptr = std::make_unique<Spline>(std::move(s));
	splines.push_back(std::move(ptr));
	return splines.back().get();
};

Spline* SplineManager::getSplineById(const std::string& id) {
	for (const auto& ptr : splines) {
		if (ptr->getId() == id) {
			return ptr.get();
		}
	}

	return nullptr;
};

Point* SplineManager::addPointToSpline(const std::string& id, Point p) {
	Spline* s = getSplineById(id);
	if (s == nullptr) return nullptr;

	return s->addPoint(std::move(p));
};

Point* SplineManager::addPointToSpline(Spline& s, Point p) {
	return s.addPoint(std::move(p));
};

Point* SplineManager::addPointToSpline(const std::string& idSpline, float t, float v) {
	Spline* s = getSplineById(idSpline);
	if (s == nullptr) return nullptr;

	return s->addPoint(t, v);
};

Point* SplineManager::addPointToSpline(Spline& s, float t, float v) {
	return s.addPoint(t, v);
};

bool SplineManager::removePointFromSpline(const std::string& id, size_t index) {
	Spline* s = getSplineById(id);
	if (s == nullptr) return false;

	return s->removePointAtIndex(index);
};

bool SplineManager::removePointFromSpline(const std::string& id, Point* p) {
	Spline* s = getSplineById(id);
	if (s == nullptr) return false;

	return s->removePoint(p);
};

Spline* SplineManager::getSplineAtIndex(size_t index) {
	if (index < splines.size()) {
		return splines[index].get();
	};

	return nullptr;
};

const std::vector<std::unique_ptr<Spline>>& SplineManager::getSplines() const {
	return splines;
};

void SplineManager::clear() {
	splines.clear();
}