#pragma once
#include "Settings.h"
#include "Board.h"
#include "Point.h"
#include "Game.h"

#include "Barrels.h"
#include "Steps.h"
#include "Results.h"
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
class Game;
class Barrels;
class GameMode; // Forward declaration
class SaveMode;
class LoadMode;
class General
{
	bool isLoad;
	bool isSilent;
	bool isSave;
public:
	General(bool _isLoad, bool _isSilent, bool _isSave) : isLoad(_isLoad), isSilent(_isSilent), isSave(_isSave) {}
	~General() {
		delete this->gameMode;
	}
	void start();
	friend class GameMode;
	friend class SaveMode;
	friend class LoadMode;
private:
	Board board;
	Game game;
	GameMode* gameMode;
	vector <Point> L_Pos;
	std::mt19937 gen; // Random generator
	std::uniform_int_distribution<> dist;
	Steps steps;
	Results results;
	pair <size_t, Results::ResultValue> pair, scorePair;
	long randomSeed;
	char keyPress = ' ';
	bool gameOver = false;
	bool pause = false;
	bool countinue = false;
	bool winGame = false;
	bool exit = false;
	bool isValid = false;
	bool potIsValid = false;
	bool duringClimb = false;
	bool hammerAttack = false;
	bool usedHammer = false;
	bool prev = false;
	bool unmatchingResultFile = false;
	string menuFile, gameOverPrint, instructionsFile, winFile, escFile;
	size_t currBoardNum = 0;
	eDirection currDir = eDirection::STAY;
	eDirection potDir = eDirection::STAY;
	vector <Moves> characterLoc;
	vector <Moves> movesV;
	vector <Moves> prevMovesV;
	vector <validText> boards;
	vector <string> fileNames;
	void gotoxy(int x, int y); //Can't be const beacause there are assignments for variables
	void clrscr();
	void draw(char ch, Point point); //Uses gotoxy so it can not be const
	eDirection checkValid(char key, bool& isValid);
	void ShowConsoleCursor(bool showFlag);
	void drawMovesList(vector <Moves>& movesV);
	void printLives(); //Same reason
	void checkLives();
	void GameOn();
	void collectBoards();
	void initGame();
	void GameRunning();
	void duringPause();
	void getFileNames();
	void uploadBoards();
	void checkValidBoard(validText& board);
	bool checkInnerSize(const vector<vector<char>> board);
	bool chooseBoard(int input);
	void printBoard();
	void resetGame();
	void myPrint(string fileName);
	void printInstructions();
	void addStepToSteps(size_t iteration);
	void addResultToResults(size_t iteration);
};

