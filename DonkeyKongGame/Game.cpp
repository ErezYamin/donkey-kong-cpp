#include "Game.h"
#include "Board.h" 
#include "Hammer.h"
#include "Barrels.h"
#include "Ghost.h"
#include "Mario.h"
#include "Direction.h"
#include "Point.h"
bool Game::getIfMarioDied()const {
	return this->marioDied;
}
void Game::setRandomGenerator(std::mt19937& generator) {// change gen to ref
	gen = &generator;
}
int Game::getRandomNumber() {
	return dist(*gen); // Use the shared generator to generate a random number
}
int Game::getCurrScore()const {
	return this->score;
}
bool Game::getIfWin()const {
	return this->winGame;
}
int Game::getCurrLives()const {
	return this->currLive;
}
void Game::setGameBoard(Board& _board) {
	this->board = _board;
	this->rowBoard = _board.getRowBoard();
	this->colBoard = _board.getColBoard();
}
bool Game::getIfJump() const {
	return this->mario.getIsJump();
};
bool Game::getIfFall() const {
	return this->mario.getIsFall();
};
bool Game::getIfClimb() const {
	return this->mario.getIsClimb();
};
bool Game::getIfNewRound() const {
	return this->reset;
};
bool Game::getIfGetHammer()const {
	return this->marioGetHammer;
}
void Game::initCharacterPlaces(vector <Moves> characterLoc) {
	this->winGame = false;
	this->board.characterLocation();//delete
	Point newPoint;
	//Ghost g;
	//SpecialGhost s_ghost;
	for (Moves chLoc : characterLoc) {
		newPoint = { chLoc.x, chLoc.y };
		switch (chLoc.ch)
		{
		case MARIO_CH:
			this->Mario_Start_Pos = newPoint;
			this->mario.setCharacterPoint(Mario_Start_Pos);
			break;
		case DONKEY_CH:
			this->donkey_valid = true;
			this->Donkey_Start_Pos = newPoint;
			break;
		case PAULINE_CH:
			this->Pauline_POS = newPoint;
			break;
		case HAMMER_CH:
			this->Hammer_POS = newPoint;
			this->hammer.setCharacterPoint(newPoint);
			break;
		case GHOST_CH:
			/*g.setCharacterPoint(newPoint);
			g.setRandomDirForStart();
			this->ghostList.push_back(g);*/
			ghostList.push_back(make_shared<Ghost>());
			ghostList.back()->setCharacterPoint(newPoint);
			ghostList.back()->setRandomDirForStart(getRandomNumber());
			break;
		case SPECIAL_GHOST_CH:
			/*s_ghost.setCharacterPoint(newPoint);
			s_ghost.setRandomDirForStart();
			this->ghostList.push_back(s_ghost);*/
			ghostList.push_back(make_shared<SpecialGhost>());
			ghostList.back()->setCharacterPoint(newPoint);
			ghostList.back()->setRandomDirForStart(getRandomNumber());
			break;
		default:
			break;
		}
	}
	this->restertGhostList = this->ghostList;
}
void Game::setHammerAttack(bool b) {
	this->hammerAttack = b;
	this->hammer.setAttack(b);
}
vector <Moves> Game::run(eDirection& currDir) {
	movList.clear();
	this->currDir = currDir;
	marioMove();
	updateGhostList();
	addBarrles();
	pushToBarrlesList();
	marioMeetPauline();
	this->hammerAttack = false;
	this->hammer.setAttack(false);
	currDir = this->currDir;
	resetGame();
	return movList;
}
void Game::marioMove() {
	Moves mov;
	Point potPoint;
	this->marioDied = false;
	this->prevMarioPoint = this->mario.getCharacterPoint();
	updateMarioFlags();
	this->mario.move(currDir);
	potPoint = this->mario.getCharacterPoint();
	marioValid(potPoint);
	this->mario.setCharacterPoint(potPoint);
	marioMeetHammer();
	mov = { MARIO_CH, potPoint.getPointX(),potPoint.getPointY() };
	this->movList.push_back(mov);

}
void Game::marioValid(Point& potPoint) {
	marioUpDir(potPoint);
	checkBoundaries(potPoint);
	checkFloor(potPoint);
}
void Game::marioUpDir(Point& potPoint) {
	int x = potPoint.getPointX();
	int y = potPoint.getPointY();
	char underCharr = board.getChar(x, y + 1);
	if (this->mario.getIsJump()) {
		if (this->prevMarioPoint.getPointY() > y) {
			this->mario.marioJumpCounter++;// change to set
		}
		else {
			this->mario.setIsJumpDown(true);
		}
	}
	if (this->mario.getIsClimb() && floorChar(underCharr))
	{
		this->mario.setIsClimb(false);
		this->currDir = eDirection::STAY;
		this->mario.setStartGoingDown(false);
	}
}
void Game::updateMarioFlags() {
	char currChar = board.getChar(mario.getCharacterPoint().getPointX(), mario.getCharacterPoint().getPointY());
	char underChar = board.getChar(mario.getCharacterPoint().getPointX(), mario.getCharacterPoint().getPointY() + 1);
	char ledderUnderFloor = board.getChar(mario.getCharacterPoint().getPointX(), mario.getCharacterPoint().getPointY() + 2);
	if (floorChar(underChar)) {
		this->mario.setIsAboveFloor(true);
	}
	else
	{
		this->mario.setIsAboveFloor(false);
	}
	if (floorChar(currChar)) {
		this->mario.setOnFloor(true);
		this->mario.setOnLedder(false);
	}
	else if (currChar == LEDDER) {
		this->mario.setOnFloor(false);
		this->mario.setOnLedder(true);
	}
	else {
		this->mario.setOnFloor(false);
		this->mario.setOnLedder(false);
	}
	if (ledderUnderFloor == LEDDER)
	{
		this->mario.setledderUnderFloor(true);
	}
	else {
		this->mario.setledderUnderFloor(false);
	}
}
void Game::checkBoundaries(Point& potPoint) { // check if mario in board
	int x = potPoint.getPointX();
	int y = potPoint.getPointY();
	if (x >= this->colBoard - 1) {
		x = this->colBoard - 2;
	}
	else if (x < 1) {
		x = 1;
	}
	if (y > this->rowBoard - 2) {
		if (this->mario.getCharacterPoint().getPointY() == y) {
			this->mario.setIsFall(false);
			updateMarioLives();
		}
		y = this->rowBoard - 2;
	}
	else if (y < 1)
	{
		y = 1;
	}
	potPoint.setPoint(x, y);
}
void Game::checkFloor(Point& potPoint) {
	int x = potPoint.getPointX();
	int y = potPoint.getPointY();
	char under2char = this->board.getChar(x, y + 2);
	char underChar = this->board.getChar(x, y + 1);
	char currChar = this->board.getChar(x, y);
	char aboveChar = this->board.getChar(x, y - 1);
	if ((!floorChar(underChar) && (!this->mario.getIsClimb() && !this->mario.getIsJump()))) {
		potPoint.setPoint(x, y + 1);
		this->mario.setIsFall(true);
		this->mario.counterFall++;
		if (floorChar(under2char)) {
			this->mario.setIsFall(false);
		}
	}
	else if (floorChar(currChar) && this->mario.getIsJump()) {// check if there is cycling above
		potPoint.setPoint(x, this->prevMarioPoint.getPointY());
	}
	else if ((floorChar(currChar) && !this->mario.getIsClimb()) || (floorChar(currChar) && this->mario.getIsGoingDown() && !this->mario.getStartGoingDown())) {
		potPoint.setPoint(this->prevMarioPoint.getPointX(), this->prevMarioPoint.getPointY());
	}
	else if (!floorChar(under2char) && this->mario.getIsJumpDown() && this->mario.marioJumpCounter >= 1) {
		this->mario.setIsFall(true);
		this->mario.counterFall++;
	}
	else {
		this->mario.setIsFall(false);
		updateMarioLives();
		this->mario.counterFall = 0;
	}
}
bool Game::floorChar(char ch) const {
	if (ch == '-' || ch == '>' || ch == '<' || ch == '=') {
		return true;
	}
	return false;
}
void Game::updateBarrels(Barrels& barrel) {
	eDirection Edir;
	char underChar = this->board.getChar(barrel.getCharacterPoint().getPointX(), barrel.getCharacterPoint().getPointY() + 1);
	this->collsion = checkMeetMovCharacter(this->mario.getCharacterPoint(), barrel.getCharacterPoint());
	updateMarioLives();
	if (floorChar(underChar)) {
		Edir = changeFloorCharToEdir(underChar);
	}
	else {
		Edir = eDirection::DOWN;
	}
	barrel.move(Edir);
	if ((barrel.getCharacterPoint().getPointX() >= this->colBoard - 1) || (barrel.getCharacterPoint().getPointX() < 1) || (barrel.getCharacterPoint().getPointY() >= this->rowBoard)) { barrel.setExplode(true); }
	if (barrel.isExplode()) {
		checkRadius(barrel.getCharacterPoint(), this->mario.getCharacterPoint());
		updateMarioLives();
	}
	this->collsion = checkMeetMovCharacter(this->mario.getCharacterPoint(), barrel.getCharacterPoint());
	updateMarioLives();
}
void Game::marioMeetHammer() {
	Moves mov;
	if (!marioGetHammer) {
		marioGetHammer = checkMeetMovCharacter(this->mario.getCharacterPoint(), this->hammer.getCharacterPoint());
	}
	if (marioGetHammer) {
		this->hammer.setCharacterPoint(this->mario.getCharacterPoint());
		this->hammer.move(currDir);
		mov = { HAMMER_CH, hammer.getCharacterPoint().getPointX(),hammer.getCharacterPoint().getPointY() };
		this->movList.push_back(mov);
	}
}
void Game::addBarrles() {
	int randomNumber = getRandomNumber();
	if ((randomNumber < PROABILITY_TO_BARREL) && this->donkey_valid) {
		Barrels b(Donkey_Start_Pos, randomNumber);
		this->barrelList.push_back(b);
	}
}
void Game::pushToBarrlesList() {
	Moves mov;
	for (auto it = barrelList.begin(); it != barrelList.end(); ) {
		Barrels& barrel = *it;
		updateBarrels(barrel);
		if (barrel.isExplode() || (checkMeetMovCharacter(this->hammer.getCharacterPoint(), barrel.getCharacterPoint()) && this->hammerAttack)) {
			it = barrelList.erase(it);


		}
		else {
			mov = { BARREL_CH, barrel.getCharacterPoint().getPointX(), barrel.getCharacterPoint().getPointY() };
			movList.push_back(mov);
			++it;
		}
	}
}
bool Game::checkMeetMovCharacter(Point pFirst, Point movCharacter) {
	if (pFirst == movCharacter) {
		return true;
	}
	return false;
}
void Game::updateMarioLives() {
	if (!this->updateCollsion) {
		if ((this->mario.counterFall >= NUM_OFF_MARIO_FALL_MOVES) && !this->mario.getIsFall()) {
			if (!this->marioDied) {
				this->currLive--;
				this->marioDied = true;
			}
			this->mario.counterFall = 0;
			this->restertGhostList = this->ghostList;
			this->reset = true;
			this->updateCollsion = true;
		}
		else if (this->collsion) {
			if (!this->marioDied) {
				this->currLive--;
				this->marioDied = true;
			}
			this->collsion = false;
			this->restertGhostList = this->ghostList;
			this->reset = true;
			this->updateCollsion = true;
		}
	}
}
void Game::checkRadius(Point barrelP, Point marioP) {
	int barrelX = barrelP.getPointX();
	int barrelY = barrelP.getPointY();
	int marioX = marioP.getPointX();
	int marioY = marioP.getPointY();
	if (((pow(marioX - barrelX, 2)) + (pow(marioY - barrelY, 2)) <= pow(RADIUS, 2))) { // check if mario stand in radius 2 from barrel explosion
		this->collsion = true;
	}
}
void Game::resetGame() {
	this->updateCollsion = false;
	if (this->reset) {
		barrelList.clear();
		Mario newMario(Mario_Start_Pos);
		this->mario = newMario;
		this->ghostList.clear();
		for (const auto& ghost : this->restertGhostList) {
			if (dynamic_cast<SpecialGhost*>(ghost.get())) {
				ghostList.push_back(std::make_unique<SpecialGhost>(*dynamic_cast<SpecialGhost*>(ghost.get())));
			}
			else {
				ghostList.push_back(std::make_unique<Ghost>(*ghost));
			}
		}
		this->reset = false;
		this->currDir = eDirection::STAY;
		this->lastDir = eDirection::STAY;
		this->collsion = false;
		this->marioGetHammer = false;
		this->marioDied = true;
	}
	else if (this->winGame) {
		score += 500;
		barrelList.clear();
		Mario newMario;
		Hammer newHammer;
		this->mario = newMario;
		this->hammer = newHammer;
		this->reset = false;
		this->currDir = eDirection::STAY;
		this->lastDir = eDirection::STAY;
		this->collsion = false;
		this->ghostList.clear();
		this->restertGhostList.clear();
		this->marioGetHammer = false;
		this->donkey_valid = false;
		this->marioDied = false;
	}
}
void Game::marioMeetPauline() {
	int marioX = this->mario.getCharacterPoint().getPointX();
	int marioY = this->mario.getCharacterPoint().getPointY();
	if (((marioX == Pauline_POS.getPointX()) || (marioX - 1 == Pauline_POS.getPointX()) || (marioX + 1 == Pauline_POS.getPointX())) && (marioY == Pauline_POS.getPointY())) {
		this->winGame = true;
	}
}
eDirection Game::changeFloorCharToEdir(char floorChar) {
	switch (floorChar) {
	case '>'://change to const 
		return eDirection::RIGHT;
		break;
	case '<':
		return eDirection::LEFT;
		break;
	default:
		return eDirection::STAY;
		break;
	}
}
void Game::updateGhostList() {
	Moves mov;
	char GhostChar = GHOST_CH;
	for (auto it = ghostList.begin(); it != ghostList.end(); ) {
		Ghost* ghost = it->get();
		this->collsion = checkMeetMovCharacter(this->mario.getCharacterPoint(), ghost->getCharacterPoint());
		updateMarioLives();
		if (this->hammerAttack && checkMeetMovCharacter(this->hammer.getCharacterPoint(), ghost->getCharacterPoint())) {
			it = this->ghostList.erase(it);
			this->collsion = false;
			score += 100;
		}
		else {
			updateGhost(*ghost);
			this->collsion = checkMeetMovCharacter(this->mario.getCharacterPoint(), ghost->getCharacterPoint());
			if (this->hammerAttack && checkMeetMovCharacter(this->hammer.getCharacterPoint(), ghost->getCharacterPoint())) {
				it = this->ghostList.erase(it);
				this->collsion = false;
				score += 100;
			}
			else {
				if (auto* specialGhost = dynamic_cast<SpecialGhost*>(ghost)) { GhostChar = SPECIAL_GHOST_CH; }
				mov = { GhostChar, ghost->getCharacterPoint().getPointX(), ghost->getCharacterPoint().getPointY() };
				this->movList.push_back(mov);
				++it;
			}
			updateMarioLives();
		}
		GhostChar = GHOST_CH;
	}

}
void Game::changeGhostEdir(eDirection& lastEdir) {
	int randomNumber = getRandomNumber();
	if (randomNumber < PROABILITY_TO_GHOST_CHANGE_DIR) {
		changeToOpEdir(lastEdir);
	}
}
void Game::changeToOpEdir(eDirection& lastEdir) {
	if (lastEdir == eDirection::RIGHT) {
		lastEdir = eDirection::LEFT;
	}
	else
	{
		lastEdir = eDirection::RIGHT;
	}
}
bool Game::checkLimits(Point& potPoint) {
	int x = potPoint.getPointX();
	int y = potPoint.getPointY();
	char underChar = this->board.getChar(x, y + 1);
	char currChar = this->board.getChar(x, y);
	checkBoundaries(potPoint);
	if (!floorChar(underChar) || floorChar(currChar) || potPoint.getPointX() != x || potPoint.getPointY() != y) {
		return true;
	}
	return false;
}
void Game::updateGhost(Ghost& ghost) {
	Point potPoint;
	eDirection lastEdir;
	eDirection down = eDirection::DOWN;
	bool isChange;
	bool s_Ghost_climb = false;
	potPoint = ghost.getCharacterPoint();
	//isChange = checkLimits(potPoint);
	//if (isChange) {
	//	ghost.move(down);
	//}
	lastEdir = ghost.getLastEdir();
	changeGhostEdir(lastEdir);
	if (auto* s_Ghost = dynamic_cast<SpecialGhost*>(&ghost)) {
		s_Ghost_climb = checkLedderForSpecialGhost(*s_Ghost);
	}
	ghost.move(lastEdir);
	potPoint = ghost.getCharacterPoint();
	isChange = checkLimits(potPoint);
	if (isChange && !s_Ghost_climb) {
		changeToOpEdir(lastEdir);
		ghost.setLastEdir(lastEdir);
		ghost.move(lastEdir);
		potPoint = ghost.getCharacterPoint();
	}
	ghost.setCharacterPoint(potPoint);

}
bool Game::checkLedderForSpecialGhost(SpecialGhost& ghost) {
	Point specialGhostPoint = ghost.getCharacterPoint();
	int randomNumber = getRandomNumber();
	char currChar = this->board.getChar(specialGhostPoint.getPointX(), specialGhostPoint.getPointY());
	char underChar = this->board.getChar(specialGhostPoint.getPointX(), specialGhostPoint.getPointY() + 1);
	char ledderUnderFloor = this->board.getChar(specialGhostPoint.getPointX(), specialGhostPoint.getPointY() + 2);
	if ((currChar == LEDDER && !ghost.canClimbDown) || (floorChar(currChar) && ghost.canClimb)) {
		if (randomNumber < PROABILITY_TO_GHOST_CLIMB || ghost.canClimb) {
			ghost.canClimb = true;
			ghost.canClimbDown = false;
			return true;
		}
	}
	else { ghost.canClimb = false; }
	if (ledderUnderFloor == LEDDER || (ghost.canClimbDown && !floorChar(underChar))) {
		if (randomNumber < PROABILITY_TO_GHOST_CLIMB || ghost.canClimbDown) {
			ghost.canClimbDown = true;
			ghost.canClimb = false;
			return true;
		}
	}
	else { ghost.canClimbDown = false; }
	return false;
}