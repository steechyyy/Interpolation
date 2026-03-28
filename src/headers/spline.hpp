#pragma once

#ifndef SPLINE_H
#define SPLINE_H

#include <string>
#include <vector>

#include "InteractableGraphPoint.hpp"

using namespace geode::prelude;

class Spline {
private:
	std::string id;
	std::vector<InteractableGraphPoint*> points;

public:

	// constructor2
	Spline(std::string_view idNew); // & = nix wird veraendert am eingabewert
	// Spline(const std::string& idNew, std::vector<std::unique_ptr<Point>>& newPoints); // might not exist anymore
	Spline(std::string_view idNew,  CCArray* objs); // the best constructor

	//getters
	const std::vector<InteractableGraphPoint*> getPoints() const; // bruh
	std::string_view getId() const; // gets iD
	InteractableGraphPoint* getPointAtIndex(size_t index); 	// hacks the us navy

	//setters
	InteractableGraphPoint* addPoint(InteractableGraphPoint* p); // woah
	InteractableGraphPoint* addPoint(float t, float v); // construct points from.. uh.. not a point

	bool removePointAtIndex(size_t index);
	bool removePoint(InteractableGraphPoint* p);
	void clear(); 	// clear the thing

	template<typename Func>
	void forEachPoint(Func f) const {
		for (auto& p : points) {
			f(*p);
		}
	}

	
};

#endif 