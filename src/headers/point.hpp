#pragma once

class Spline;

class Point {
public:
	float time;
	float value;
	Spline* spline;

	// construct new point v3
	Point();

	// construct new point v2
	Point(float time, float value);

	// construct new point
	Point(float time, float value, Spline* spline);

	// get time
	float getTime();

	// get value
	float getValue();

	// get spline owner
	Spline* getSpline();
};