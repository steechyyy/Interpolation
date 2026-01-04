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
	Spline(const std::string& idNew, const std::vector<Point>& newPoints); // costructor
	Spline(const std::string& idNew, const CCArray* objs); // the best constructor

	//geters
	const std::vector<Point>& getPoints() const; // bruh
	const std::string& getId() const; // gets iD
	Point* getPointAtIndex(size_t index); 	// hacks the us navy

	//seters
	Point& addPoint(Point p); // bruh 2
	Point& addPoint(float t, float v); // construct points from.. uh.. not a point
	void clear(); 	// clear the thing

};

#endif 