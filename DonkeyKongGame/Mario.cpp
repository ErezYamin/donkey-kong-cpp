#include "Mario.h"
void Mario::setStartGoingDown(bool b) {
	this->startClimbDown = b;
}
void Mario::setIsJumpDown(bool b) {
	this->jumpDown = b;
}
void Mario::setIsAboveFloor(bool b) {
	this->aboveFloor = b;
}
void Mario::setOnFloor(bool b) {
	this->onFloor = b;
}
void Mario::setOnLedder(bool b) {
	this->onLedder = b;
}
void Mario::setledderUnderFloor(bool b) {
	this->ledderUnderFloor = b;
}
void Mario::setIsFall(bool b) {
	this->isFall = b;
}
void Mario::setIsClimb(bool b) {
	this->isClimb = b;
}
bool Mario::getIsFall()const {
	return this->isFall;
}
bool Mario::getIsJump()const {
	return this->isJump;
}
bool Mario::getIsClimb()const {
	return this->isClimb;
}
bool Mario::getIsGoingDown()const {
	return this->goingDown;
}
bool Mario::getIsJumpDown()const {
	return this->jumpDown;
}
bool Mario::getStartGoingDown()const {
	return this->goingDown;
}
void Mario::move(eDirection& currDir) {
	this->currDir = currDir;
	if (isFall && !this->jumpDown) {
		this->dir.convertEdirToDir(eDirection::DOWN);
	}
	else {
		switch (this->currDir)
		{
		case eDirection::LEFT:
			if (!this->isClimb) {
				this->dir.convertEdirToDir(currDir);
				this->isWalkingRight = false;
				this->isWalkingLeft = true;
				this->lastEdir = currDir;
			}
			else
			{
				this->dir.convertEdirToDir(this->lastEdir);
				this->currDir = this->lastEdir;
			}
			break;
		case eDirection::RIGHT:
			if (!this->isClimb) {
				this->dir.convertEdirToDir(currDir);
				this->isWalkingRight = true;
				this->isWalkingLeft = false;
				this->lastEdir = currDir;
			}
			else
			{
				this->dir.convertEdirToDir(this->lastEdir);
				currDir = this->lastEdir;
			}
			break;
		case eDirection::STAY:
			if (!this->isJump) {
				dir.convertEdirToDir(currDir);
				this->isWalkingRight = false;
				this->isWalkingLeft = false;
				this->goingDown = false;
				this->lastEdir = currDir;
			}
			else {
				this->dir.convertEdirToDir(lastEdir);
				currDir = this->lastEdir;
			}
			break;
		case eDirection::UP:
			this->dir.convertEdirToDir(currDir);
			this->goingDown = false;
			if ((this->onLedder || this->isClimb) && (!this->isJump)) {
				this->isClimb = true;
				this->lastEdir = this->currDir;
			}
			else {
				marioJump();
				this->lastEdir = currDir;
			}
			break;
		case eDirection::DOWN:
			if (this->onLedder && this->isClimb) {
				this->dir.convertEdirToDir(currDir);
				if (this->isClimb) {
					this->startClimbDown = false;
					this->goingDown = true;
					this->isClimb = true;
				}
			}
			else if (this->isJump) {
				this->dir.convertEdirToDir(currDir);
				marioJump();
			}
			else if ((this->ledderUnderFloor && !this->isClimb) || this->startClimbDown) {
				this->startClimbDown = true;
				this->dir.convertEdirToDir(currDir);
				this->isClimb = true;
			}
			else {
				changeToLastDir();
			}
			break;
		default:
			break;
		}
		this->updatePoint();
		this->lastPoint = this->point;
		currDir = this->currDir;
	}
}
void Mario::marioJump() {
	this->isJump = true;
	if (this->marioJumpCounter == 0 && this->jumpDown == true) {
		this->jumpDown = false;
		this->isJump = false;
		changeToLastDir();
	}
	if (this->jumpDown || this->marioJumpCounter > 1) {
		this->currDir = eDirection::DOWN;
		this->dir.convertEdirToDir(this->currDir);
		this->marioJumpCounter--;
		this->jumpDown = true;
	}
	isJumpDuringWalk();
}
void Mario::isJumpDuringWalk() {
	if (this->isWalkingRight) {
		this->dir.setDirX(1);
	}
	else if (this->isWalkingLeft) {
		this->dir.setDirX(-1);
	}
}
void Mario::changeToLastDir() {
	if (isWalkingRight) {
		this->currDir = eDirection::RIGHT;
	}
	else if (isWalkingLeft)
	{
		this->currDir = eDirection::LEFT;
	}
	else if (isJump) {
		this->currDir = eDirection::UP;
	}
	else {
		this->currDir = eDirection::STAY;
	}
	dir.convertEdirToDir(currDir);
}