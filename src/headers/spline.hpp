#ifndef SPLINE_H
#define SPLINE_H

#include <string>
#include <vector>
#include <cstddef>

class Point;

class Spline {
private:
	std::string id;
	std::vector<Point*> points;

public:

	// constructor2
	Spline(const std::string idNew);

	// costructor
	Spline(const std::string idNew, const std::vector<Point*>& newPoints);

	// bruh 2
	Point* addPoint(Point* p);

	// clear the thing
	void clear();

	// gets iD
	const std::string getId();

	// hacks the us navy
	Point* getPointAtIndex(size_t index);

	// bruh
	const std::vector<Point*>& getPoints() const;

};

#endif 