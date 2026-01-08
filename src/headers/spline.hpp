#pragma once

#ifndef SPLINE_H
#define SPLINE_H

#include <string>
#include <vector>
#include <cstddef>

#include "point.hpp"

using namespace geode::prelude;

class Spline {
private:
	std::string id;
	std::vector<std::unique_ptr<Point>> points;

public:

	// constructor2
	Spline(const std::string& idNew); // & = nix wird veraendert am eingabewert
	// Spline(const std::string& idNew, std::vector<std::unique_ptr<Point>>& newPoints); // might not exist anymore
	Spline(const std::string& idNew, const CCArray* objs); // the best constructor

	//getters
	const std::vector<std::unique_ptr<Point>>& getPoints() const; // bruh
	const std::string& getId() const; // gets iD
	Point* getPointAtIndex(size_t index); 	// hacks the us navy

	//setters
	Point* addPoint(Point&& p); // bruh 2
	Point* addPoint(float t, float v); // construct points from.. uh.. not a point

	bool removePointAtIndex(size_t index);
	bool removePoint(Point* p);
	void clear(); 	// clear the thing

	
};

#endif 