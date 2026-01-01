#pragma once

class Point;

class Spline {
public:
	std::string id;
	std::vector<Point> points;

	// constructor2
	Spline(std::string idNew);

	// costructor
	Spline(std::string idNew, std::vector<Point>);


	// bruh 2
	void addPoint(Point);

	//gets iD
	std::string getId();

	// hacks the us navy
	Point* getPointAtId(int index);

	// bruh
	std::vector<Point> getPoints();

};