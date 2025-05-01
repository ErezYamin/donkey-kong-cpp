#pragma once
#include "Point.h"
#include "Direction.h"
#include "Settings.h"
class Character
{
protected:
	Point point;
	char characterChar;
	Direction dir;
	eDirection lastEdir;
	void updatePoint();
public:
	Character(int x, int y, char ch, Direction dir) : point(x, y), characterChar(ch), dir(dir), lastEdir(eDirection::STAY) {}
	Character(int x, int y, char ch) : point(x, y), characterChar(ch), dir({ 0,0 }), lastEdir(eDirection::STAY) {}
	Character(char ch) : point(1, 1), characterChar(ch), dir({ 0,0 }), lastEdir(eDirection::STAY) {}
	void setCharacterPoint(Point p);
	Point getCharacterPoint()const;
	Direction getCharacterDir() const;
	void setCharacterDir(Direction _dir);
	char getCharacterChar() const;
	virtual void move(eDirection& currDir) = 0;
	void setRandomDirForStart(int random);
};
