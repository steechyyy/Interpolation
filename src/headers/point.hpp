#pragma once

#ifndef POINT_H
#define POINT_H

class Spline;

class Point {
private:
	float time;
	float value;
	std::string type;
	Spline* spline;
	GameObject* obj;

public:


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

	//Sets the object which this point is linked to
	void setObj(GameObject* obj);
	
	//sets the data type of the value attribute
	void setType(const std::string& type);

	//set parent spline
	void setSpline(Spline* s);

	// Returns
	GameObject* getObj() const;

	// get time
	float getTime() const;

	// get value
	float getValue() const;

	// get spline owner
	Spline* getSpline() const;
};

#endif