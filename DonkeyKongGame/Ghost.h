#pragma once
#include "Character.h"
class Ghost : public Character
{
public:
	Ghost(Point startPos) :Character(startPos.getPointX(), startPos.getPointY(), GHOST_CH) {}
	Ghost() : Character(GHOST_CH) {}
	Ghost(Point startPos, char specialChar) : Character(startPos.getPointX(), startPos.getPointY(), specialChar) {}
	Ghost(char specialChar) : Character(specialChar) {}
	virtual void move(eDirection& currDir) override;
	eDirection getLastEdir() const;
	void setLastEdir(eDirection currDir);
};
