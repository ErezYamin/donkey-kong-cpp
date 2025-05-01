#pragma once
#include "Character.h"
class Mario : public Character
{
	bool isWalkingRight = false;
	bool isWalkingLeft = false;
	bool isJump = false;
	bool onLedder = false;
	bool isFall = false;
	bool isClimb = false;
	bool jumpDown = false;
	bool goingDown = false;
	bool ledderUnderFloor = false;
	bool onFloor = false;
	bool startClimbDown = false;
	bool aboveFloor = false;
	Point lastPoint;
	eDirection lastEdir = eDirection::STAY;
	eDirection currDir = eDirection::STAY;
	void marioJump();
	void isJumpDuringWalk();
	void changeToLastDir();
public:
	Mario() : Character(MARIO_CH) {}
	Mario(Point mario_start) : Character(mario_start.getPointX(), mario_start.getPointY(), MARIO_CH) {}
	virtual void move(eDirection& currDir) override;
	void setStartGoingDown(bool b);
	void setIsJumpDown(bool b);
	void setIsAboveFloor(bool b);
	void setOnFloor(bool b);
	void setOnLedder(bool b);
	void setledderUnderFloor(bool b);
	void setIsClimb(bool b);
	void setIsFall(bool b);
	bool getIsFall()const;
	bool getIsJump()const;
	bool getIsClimb()const;
	bool getIsGoingDown()const;
	bool getIsJumpDown()const;
	bool getStartGoingDown()const;
	int counterFall = 0;
	bool collsion = false;
	int marioJumpCounter = 0;

};
