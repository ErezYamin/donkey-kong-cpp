#include "Direction.h"
void Direction::convertEdirToDir(eDirection currEdir) {
	switch (currEdir)
	{
	case eDirection::STAY:
		this->x = 0;
		this->y = 0;
		break;
	case eDirection::UP:
		this->x = 0;
		this->y = -1;
		break;
	case eDirection::DOWN:
		this->x = 0;
		this->y = 1;
		break;
	case eDirection::RIGHT:
		this->x = 1;
		this->y = 0;
		break;
	case eDirection::LEFT:
		this->x = -1;
		this->y = 0;
		break;
	default:
		this->x = 0;
		this->y = 0;
		break;
	}
}
int Direction::getDirX() const {
	return this->x;
}
int Direction::getDirY() const {
	return this->y;
}
void Direction::setDirX(int _x) {
	this->x = _x;
}
void Direction::setDirY(int _y) {
	this->y = _y;
}