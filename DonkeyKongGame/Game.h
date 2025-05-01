#pragma once
#include "Settings.h"
#include "Mario.h"
#include "Ghost.h"
#include "Hammer.h"
#include "Barrels.h"
#include "Point.h"
#include "Direction.h"
#include "Board.h"
#include "SpecialGhost.h"
class Board;
class Barrels;
class Ghost;
class Hammer;
class Mario;
class Game
{
	Mario mario;
	Board board;
	vector <Moves> movList;
	vector <Barrels> barrelList;
	vector <Point> ghostPos;
	vector <shared_ptr<Ghost>> ghostList;
	vector <shared_ptr<Ghost>> restertGhostList;
	Hammer hammer;
public:
	Game() : lastDir(eDirection::STAY), currDir(eDirection::STAY) {}
	void initCharacterPlaces(vector <Moves> characterLoc);
	vector <Moves> run(eDirection& currDir);
	bool getIfMarioDied()const;
	bool getIfWin()const;
	bool getIfGetHammer()const;
	bool getIfJump()const;
	bool getIfFall()const;
	bool getIfClimb()const;
	bool getIfNewRound()const;
	void setHammerAttack(bool b);
	void setGameBoard(Board& _board);
	int getCurrLives()const;
	int getCurrScore()const;
	void setRandomGenerator(std::mt19937& generator);
private:
	std::mt19937* gen = nullptr;
	std::uniform_int_distribution<> dist{ 1, 100 };
	eDirection currDir;
	eDirection lastDir;
	Point Mario_Start_Pos;
	Point Donkey_Start_Pos;
	Point Pauline_POS;
	Point Hammer_POS;
	Point prevMarioPoint;
	int currLive = 3;
	int score = 0;
	int rowBoard = BOARD_GAME_HEIGHT;
	int colBoard = BOARD_GAME_WIDTH;
	void marioValid(Point& potPoint); //Checks mario's validation
	void marioUpDir(Point& potPoint); //Checks mario's up direction
	bool collsion = false;
	bool hammerAttack = false;
	bool reset = false;
	bool marioGetHammer = false;
	bool winGame = false;
	bool donkey_valid = false;
	bool updateCollsion = false;
	bool marioDied = false;
	void marioMove();
	void updateMarioFlags(); //Updates the bool variables of mario
	void checkBoundaries(Point& potPoint);
	void checkFloor(Point& potPoint); //Checks the floor and if there is a ceiling
	bool floorChar(char ch)const; //Cheks if it is a legit floor char
	void updateBarrels(Barrels& barrel); //Update the barrel's move
	void addBarrles(); //Adds barrels to the list
	void pushToBarrlesList();
	eDirection changeFloorCharToEdir(char floorChar);
	void updateMarioLives();
	bool checkMeetMovCharacter(Point pFirst, Point movCharacter); //Checks if mario meet a different object
	void checkRadius(Point barrelP, Point marioP); //Calculates the barrels explosion range
	void resetGame();
	void marioMeetPauline();
	void updateGhostList();
	void changeGhostEdir(eDirection& lastEdir);
	bool checkLimits(Point& potPoint); //Checks if the ghosts are above a floor
	void changeToOpEdir(eDirection& lastEdir); //Switch the direction
	void updateGhost(Ghost& ghost);
	void marioMeetHammer();
	bool checkLedderForSpecialGhost(SpecialGhost& ghost);
	int getRandomNumber();
};