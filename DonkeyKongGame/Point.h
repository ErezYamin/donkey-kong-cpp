#pragma once
#include "Settings.h"
class Point
{
	int x, y;
public:
	Point(int x, int y) : x(x), y(y) {}
	Point() : x(0), y(0) {}
	bool operator==(const Point& other) const {
		return (x == other.x && y == other.y);
	}
	void setPoint(int x, int y);
	int getPointX()const;
	int getPointY()const;

};

