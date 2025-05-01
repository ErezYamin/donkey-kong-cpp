#pragma once
#include "Character.h"
class Hammer : public Character
{
public:
	Hammer() : Character(HAMMER_CH), hammerAttack(false) {}
	virtual void move(eDirection& currDir)override;
	void updateHammerDir(eDirection& currDir);
	void setAttack(bool b);
private:
	bool hammerAttack = false;
};
