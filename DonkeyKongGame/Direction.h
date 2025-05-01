#pragma once
#include "Settings.h"
class Direction
{
	int x, y;
public:
	Direction() : x(0), y(0) {}
	Direction(int _x, int _y) : x(_x), y(_y) {}
	void convertEdirToDir(eDirection currEdir);
	int getDirX() const;
	int getDirY() const;
	void setDirX(int x);
	void setDirY(int y);
};
