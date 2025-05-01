#include "Point.h"
void Point::setPoint(int x, int y) {
	this->x = x;
	this->y = y;
}
int Point::getPointX() const {
	return this->x;
}
int Point::getPointY()const {
	return this->y;
}