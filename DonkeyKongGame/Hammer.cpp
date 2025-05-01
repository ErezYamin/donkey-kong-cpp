#include "Hammer.h"
void Hammer::move(eDirection& currDir) {
	eDirection curr = currDir;
	updateHammerDir(curr);
	this->dir.convertEdirToDir(curr);
	if (!this->hammerAttack) {
		this->dir.setDirY(-1);
	}
	else
	{
		this->dir.setDirY(0);
	}
	this->updatePoint();
}
void Hammer::updateHammerDir(eDirection& currDir) {
	if (currDir == eDirection::RIGHT || currDir == eDirection::LEFT) {
		this->lastEdir = currDir;
	}
	else {
		currDir = this->lastEdir;
	}
}
void Hammer::setAttack(bool b) {
	this->hammerAttack = b;
}