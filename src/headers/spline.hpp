#ifndef SPLINE_H
#define SPLINE_H

#include <string>
#include <vector>
#include <cstddef>
#include <common.hpp>

using namespace geode::prelude;


class Point;

class Spline {
private:
	std::string id;
	std::vector<Point> points;

public:

	// constructor2
	Spline(const std::string& idNew); // & = nix wird veraendert am eingabewert

	// costructor
	Spline(const std::string& idNew, const std::vector<Point>& newPoints);

	// the best constructor
	Spline(const std::string& idNew, const CCArray* objs);

	// bruh 2
	Point& addPoint(Point p);

	// construct points from.. uh.. not a point
	Point& addPoint(float t, float v);

	// clear the thing
	void clear();

	// gets iD
	const std::string& getId() const;

	// hacks the us navy
	Point* getPointAtIndex(size_t index);

	// bruh
	const std::vector<Point>& getPoints() const;

};

#endif 