#include <common.hpp>
#include <SplineManager.hpp>

using namespace geode::prelude;

Spline* SplineManager::newSpline(const std::string& id) {
	Spline s(id);
	splines.push_back(s);
	return &splines.back();
};

Spline* SplineManager::newSpline(const std::string& id, const std::vector<Point>& points) {
	Spline s(id, points);
	splines.push_back(s);
	return &splines.back();
};

Spline* SplineManager::newSpline(const std::string& id, const CCArray* objs) {
	Spline s(id, objs);
	splines.push_back(s);
	return &splines.back();
};

Spline& SplineManager::addSpline(Spline spline) {
	splines.push_back(spline);
	return splines.back();
};

Point* SplineManager::addPointToSpline(const std::string& idSpline, Point p) {
	if (auto* s = SplineManager::getSplineFromId(idSpline)) {
		return &s->addPoint(p);
	};

	return nullptr;
};

Point* SplineManager::addPointToSpline(Spline& s, Point p) {
	s.addPoint(p);
	return &s.getPoints().back();
};

Point* SplineManager::addPointToSpline(const std::string& idSpline, float t, float v) {
	Spline* s = SplineManager::getSplineFromId(idSpline);
	if (s == nullptr) { return nullptr; };

	s->addPoint(t, v);
	return &s->getPoints().back();
};

Point* SplineManager::addPointToSpline(Spline& s, float t, float v) {
	s.addPoint(t, v);
	return &s.getPoints().back();
};

Spline* SplineManager::getSplineAtIndex(size_t index) {
	if (index < splines.size()) {
		return &splines[index];
	};

	return nullptr;
};

Spline* SplineManager::getSplineFromId(const std::string& id) {
	auto it = std::find_if(
		splines.begin(),
		splines.end(),
		[&](Spline& s) { return s.getId() == id; }
	);

	return it != splines.end() ? &(*it) : nullptr;
}

const std::vector<Spline>& SplineManager::getSplines() const {
	return splines;
};