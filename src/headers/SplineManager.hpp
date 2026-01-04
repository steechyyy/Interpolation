#ifndef SPLINEMANAGER_H
#define SPLINEMANAGER_H

#include <common.hpp>

using namespace geode::prelude;

class Point;
class Spline;

class SplineManager {
private:
	std::vector<Spline>& splines;

public:

	Spline* newSpline(const std::string& id);
	Spline* newSpline(const std::string& id, const std::vector<Point>& newPoints);
	Spline* newSpline(const std::string& id, const CCArray* objs);

	Spline& addSpline(Spline spline);

	Point* addPointToSpline(const std::string& idSpline, Point p);
	Point* addPointToSpline(Spline& s, Point p);
	Point* addPointToSpline(const std::string& idSpline, float t, float v);
	Point* addPointToSpline(Spline& s, float t, float v);

	Spline* getSplineAtIndex(size_t index);
	Spline* getSplineFromId(std::string& id);

	const std::vector<Spline>& getSplines() const;
	
};

#endif