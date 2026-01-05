#ifndef POINT_H
#define POINT_H

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

	// no
	void setTime(float t);

	//im lazuy
	void setValue(float v);

	// get time
	float getTime() const;

	// get value
	float getValue() const;

	// get spline owner
	Spline* getSpline() const;
};

#endif