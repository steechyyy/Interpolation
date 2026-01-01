#pragma once

class Point;

class Spline {
public:
	std::string id;
	std::vector<Point*> points;

	// constructor2
	Spline(std::string idNew);

	// costructor
	Spline(std::string idNew, std::vector<Point*>);

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