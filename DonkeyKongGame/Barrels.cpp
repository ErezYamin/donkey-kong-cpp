#include "Barrels.h"
void Barrels::onEqualFloor() {
	if (this->start && this->lastEdir == eDirection::STAY) {
		this->setRandomDirForStart(this->randomNumber);
	}
	this->start = false;
}
void Barrels::checkExplode() {
	if (this->barrelFallCounter >= NUM_OFF_BARREL_FALL_MOVES) {
		this->explode = true;
	}
	else
	{
		this->barrelFallCounter = 0;
	}
}
void Barrels::move(eDirection& currDir) {
	if (currDir == eDirection::STAY) {
		onEqualFloor();
		dir.convertEdirToDir(this->lastEdir);
		currDir = this->lastEdir;
	}
	else
	{
		dir.convertEdirToDir(currDir);

	}
	if (currDir == eDirection::DOWN) {
		this->barrelFallCounter++;
	}
	else {
		this->lastEdir = currDir;
		this->checkExplode();
	}
	if (!this->explode) {
		this->updatePoint();
	}
}
bool Barrels::isExplode()const {
	return this->explode;
}
void Barrels::setExplode(bool b) {
	this->explode = true;
}