#pragma once
#include "Ghost.h"
class SpecialGhost : public Ghost
{

public:
	SpecialGhost(Point startPos) : Ghost(startPos, SPECIAL_GHOST_CH) {}
	SpecialGhost() : Ghost(SPECIAL_GHOST_CH) {}
	virtual void move(eDirection& currDir) override;
	bool canClimb = false;
	bool canClimbDown = false;
};
