#include <point.hpp>


Point::Point() : time(0.0f), value(0.0f), spline(nullptr), obj(nullptr) {}
Point::Point(float t, float v) : time(t), value(v), spline(nullptr), obj(nullptr) {}
Point::Point(float t, float v, Spline* s) : time(t), value(v), spline(s), obj(nullptr) {}


void Point::setValue(float v) {
	value = v;
};

void Point::setTime(float t) {
	time = t;
};

void Point::setObj(GameObject* obj) {
	obj = obj;
}

void Point::setType(const std::string& typ) {
	type = typ;
}

void Point::setSpline(Spline* s) {
	spline = s;
}

GameObject* Point::getObj() const {
	return obj;
}

float Point::getTime() const {
	return time;
};

float Point::getValue() const {
	return value;
};

Spline* Point::getSpline() const {
	return spline;
};
