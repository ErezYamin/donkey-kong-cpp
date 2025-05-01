#include "Character.h"
void Character::setCharacterPoint(Point p) {
	this->point.setPoint(p.getPointX(), p.getPointY());
}
Point Character::getCharacterPoint() const {
	return this->point;
}
char Character::getCharacterChar() const {
	return this->characterChar;
}
Direction Character::getCharacterDir() const {
	return this->dir;
}
void Character::setCharacterDir(Direction _dir) {
	this->dir = _dir;
}
void Character::updatePoint() {
	int newPointX = this->point.getPointX() + this->dir.getDirX();
	int newPointY = this->point.getPointY() + this->dir.getDirY();
	this->point.setPoint(newPointX, newPointY);
}
void Character::setRandomDirForStart(int random) {

	if (random % 2 == 0) {
		this->setCharacterDir({ -1,0 });
		this->lastEdir = eDirection::LEFT;
	}
	else
	{
		this->setCharacterDir({ 1,0 });
		this->lastEdir = eDirection::RIGHT;
	}
}