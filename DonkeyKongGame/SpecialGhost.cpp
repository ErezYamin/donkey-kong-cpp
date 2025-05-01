#include "SpecialGhost.h"
void SpecialGhost::move(eDirection& currDir) {
	if (this->canClimb) { currDir = eDirection::UP; }
	if (this->canClimbDown) { currDir = eDirection::DOWN; }
	Ghost::move(currDir);
}
