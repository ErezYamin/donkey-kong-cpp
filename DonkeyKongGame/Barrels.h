#pragma once
#include "Character.h"
class Barrels : public Character
{
	int barrelFallCounter = 0;
	bool explode = false;
	void checkExplode();
	bool start = true;
	int randomNumber;
public:
	Barrels(Point donkey_pos, int _randomNumber) : Character(donkey_pos.getPointX(), donkey_pos.getPointY(), BARREL_CH), randomNumber(_randomNumber) {}
	Barrels() : Character(1, 1, BARREL_CH), randomNumber(PROABILITY_TO_BARREL) {}
	virtual void move(eDirection& currDir) override;
	bool isExplode()const;
	void onEqualFloor();
	void setExplode(bool b);
};