#include <point.hpp>


Point::Point() : time(0.0f), value(0.0f), spline(nullptr) {}
Point::Point(float t, float v) : time(t), value(v), spline(nullptr) {}
Point::Point(float t, float v, Spline* s) : time(t), value(v), spline(s) {}


void Point::setValue(float v) {
	value = v;
};

void Point::setTime(float t) {
	time = t;
};

float Point::getTime() {
	return time;
};

float Point::getValue() {
	return value;
};

Spline* Point::getSpline() {
	return spline;
};
