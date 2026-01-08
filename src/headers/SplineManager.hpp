#ifndef SPLINEMANAGER_H
#define SPLINEMANAGER_H

#include <common.hpp>
#include "spline.hpp"

using namespace geode::prelude;

class Point;
class Spline;

class SplineManager {
private:
	std::vector<std::unique_ptr<Spline>> splines;
	SplineManager() {};

public:

	Spline* newSpline(const std::string& id);
	//Spline* newSpline(const std::string& id, const std::vector<Point>& newPoints);
	Spline* newSpline(const std::string& id, const CCArray* objs);

	Spline* addSpline(Spline&& s);

	Spline* getSplineById(const std::string& id);

	Point* addPointToSpline(const std::string& id, Point p);
	Point* addPointToSpline(Spline& s, Point p);
	Point* addPointToSpline(const std::string& id, float t, float v);
	Point* addPointToSpline(Spline& s, float t, float v);

	bool removePointFromSpline(const std::string& id, size_t index);
	bool removePointFromSpline(const std::string& id, Point* p);

	Spline* getSplineAtIndex(size_t index);

	const std::vector<std::unique_ptr<Spline>>& getSplines() const;

	static SplineManager& get() {
		static SplineManager instance;
		return instance;
	};

	// get rid of everything spline
	void clear();
};

#endif