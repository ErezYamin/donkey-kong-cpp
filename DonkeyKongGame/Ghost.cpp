#include "Ghost.h"
void Ghost::move(eDirection& currDir) {
	this->dir.convertEdirToDir(currDir);
	this->updatePoint();
}
eDirection Ghost::getLastEdir() const {
	return this->lastEdir;
}
void Ghost::setLastEdir(eDirection currDir) {
	this->lastEdir = currDir;
}