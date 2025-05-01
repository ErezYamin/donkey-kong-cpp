#include "General.h"
#include "GameMode.h"  // Now safe to include
#include "LoadMode.h"
#include "SaveMode.h"
#include "Game.h"
#include "Board.h"
#include "Barrels.h"
#include "Point.h"
#include <fstream>
#include "WindowsUtils.h"
namespace fs = std::filesystem;
using namespace std;
void General::ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO  cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void General::start() {
	if (this->isLoad) { this->gameMode = new LoadMode(*this, isSilent); }
	else {
		this->gameMode = new SaveMode(*this, isSave);
	}
	ShowConsoleCursor(false);
	collectBoards();
	this->gameMode->currMode();
}
void General::collectBoards() {
	getFileNames();
	uploadBoards();
}
void General::GameOn() {
	int choseIndex = this->gameMode->displayBoards();
	int currIndex;
	int range = this->boards.size();
	for (size_t i = 0; i < range; i++) {
		currIndex = (choseIndex + i) % range;
		if (this->boards[currIndex].valid && !this->boards[currIndex].used) {
			this->currBoardNum = currIndex;
			this->board.setBoard(this->boards[currIndex].text);
			initGame();
			printBoard();
			printLives();
			while (!this->gameOver && !this->winGame) {
				GameRunning();
				this->boards[currIndex].used = true;
				this->gameMode->handleVectorResultsAndSteps();
			}
			if (this->game.getCurrLives() > 0 && !this->exit && !this->unmatchingResultFile) {
				resetGame();
				clrscr();
				if (!this->isSilent) { Sleep(200); }

			}
			else if (this->exit && this->gameOver) {
				i = range;
				clrscr();
				myPrint(this->gameOverPrint);
			}
			else {
				if (!this->isSilent) {
					clrscr();
					myPrint(this->gameOverPrint);
					Sleep(350);
				}
				for (int i = 0; i < range; i++) {
					this->boards[i].used = false;
				}
				i = range;
				clrscr();
				if (!isLoad) {
					Game newGame;
					resetGame();
					this->game = newGame;
					myPrint(this->menuFile);
					this->gameMode->currMode();
				}

			}

		}
	}
	if (this->game.getIfWin() && !this->isSilent && !this->unmatchingResultFile) {
		myPrint(this->winFile);
		Sleep(400);
		clrscr();
		if (!isLoad) {
			Game newGame;
			this->game = newGame;
			resetGame();
			myPrint(this->menuFile);
			this->gameMode->currMode();
		}
	}
}
bool General::chooseBoard(int input) {
	if (input >= 0 && input <= static_cast<int>(this->fileNames.size()) && this->boards[input].valid == true) {
		if (results.isEmptyResultFile(this->boards[input].fileNameResults) || steps.isEmptyStepsFile(this->boards[input].fileNameSteps)) { return false; }
		return true;
	}
	else {
		cout << "Invalid selection.\n";
		return false;
	}
}
void General::initGame() {
	this->gameMode->initGameMode();
	this->board.reset();
	this->characterLoc = this->board.characterLocation();
	this->game.setGameBoard(this->board);
	this->game.setRandomGenerator(gen);
	this->game.initCharacterPlaces(characterLoc);
	this->unmatchingResultFile = false;
}
void General::GameRunning() {
	size_t iteration = 0;
	if (this->gameMode->checkKB(iteration) || !this->pause) {
		this->keyPress = this->gameMode->getCharGameMode();
		this->currDir = checkValid(keyPress, this->isValid);
		addStepToSteps(iteration);
		while (this->isValid && !this->pause && !this->gameOver && !this->winGame && !this->exit && !this->unmatchingResultFile) {
			this->movesV = this->game.run(this->currDir);
			checkLives();
			iteration++;
			this->prev = true;
			drawMovesList(this->prevMovesV);
			this->prev = false;
			drawMovesList(this->movesV);
			if (!isLoad) { Sleep(50); }
			else if (isLoad && !isSilent) { Sleep(20); }
			prevMovesV.clear();
			prevMovesV = movesV;
			if (this->gameMode->checkKB(iteration) && !this->game.getIfJump() && !this->game.getIfFall() && !this->game.getIfMarioDied()) {
				this->potIsValid = false;
				keyPress = this->gameMode->getCharGameMode();
				duringClimb = this->game.getIfClimb();
				potDir = checkValid(keyPress, this->potIsValid);
				this->game.setHammerAttack(this->hammerAttack);
				if (potIsValid && (potDir != currDir)) {
					currDir = potDir;
					addStepToSteps(iteration);
				}
				else if (!potIsValid && this->hammerAttack) { addStepToSteps(iteration); }
			}
			if (this->game.getIfWin()) {
				this->winGame = true;
			}
			addResultToResults(iteration);
		}
	}
}
void General::resetGame() {
	keyPress = ' ';
	this->usedHammer = false;
	gameOver = false;
	pause = false;
	winGame = false;
	exit = false;
	isValid = false;
	potIsValid = false;
	duringClimb = false;
	hammerAttack = false;
	prev = false;
	unmatchingResultFile = false;
	currDir = eDirection::STAY;
	potDir = eDirection::STAY;
	characterLoc.clear();
	movesV.clear();
	prevMovesV.clear();
}
void General::addResultToResults(size_t iteration) {
	if (this->game.getIfMarioDied()) {
		if (isLoad) {
			pair = { iteration,Results::ResultValue::LoseLife };
			if (this->results.popResult() != pair) {
				this->unmatchingResultFile = true;
				this->gameOver = true;
			}
		}
		else if (isSave) {
			results.addResult(iteration, Results::ResultValue::LoseLife);
		}
	}
	if (this->game.getIfWin()) {
		if (isSave) {
			results.addResult(iteration, Results::ResultValue::Finished);
			results.addResult(this->game.getCurrScore(), Results::ResultValue::Score);
		}
		else if (isLoad) {
			pair = { iteration,Results::ResultValue::Finished };
			scorePair = { this->game.getCurrScore() , Results::ResultValue::Score };
		}

	}
}
void General::addStepToSteps(size_t iteration) {
	if (isSave) {
		char currDirChar = (char)this->currDir;
		if (this->hammerAttack) {
			currDirChar = HAMMER_CH;
		}
		this->steps.addStep(iteration, currDirChar);
	}

}
eDirection General::checkValid(char key, bool& isValid) {
	if (key == HAMMER_CH) {
		this->hammerAttack = true;
	}
	else {
		this->hammerAttack = false;
	}
	switch (key)
	{
	case 'a': if (!this->duringClimb) { isValid = true; }; return eDirection::LEFT;
	case 's': isValid = true; return eDirection::STAY;
	case 'd': if (!duringClimb) { isValid = true; }; return eDirection::RIGHT;
	case 'w': isValid = true; return eDirection::UP;
	case 'x': isValid = true; return eDirection::DOWN;
		case char(ESC) : this->pause = true; duringPause(); isValid = true; return this->currDir;
		default:
			isValid = false;
			break;
	}
}
void General::drawMovesList(vector <Moves>& movesV) {
	if (!isSilent) {
		char prevChar;
		Point p;
		for (Moves mov : movesV) {
			p = { mov.x, mov.y };
			if (this->prev) {
				prevChar = board.getChar(p.getPointX(), p.getPointY());
				mov.ch = prevChar;
				if ((this->game.getIfGetHammer() || this->usedHammer) && prevChar == HAMMER_CH) {
					if (this->game.getIfGetHammer()) {
						this->usedHammer = true;
					}
					mov.ch = ' ';
				}
			}
			draw(mov.ch, p);
		}
		if (!this->prev) {
			if (!this->isSilent) { Sleep(10); }
		}
		else {
			movesV.clear();
		}
		this->prev = false;
	}
}
void General::duringPause() {
	clrscr();
	myPrint(this->escFile);
	char input;
	while (this->pause) {
		input = char(_getch());
		if (input == char(ESC)) {
			this->pause = false;
		}
		else if (input == '0')
		{
			this->pause = false;
			this->exit = true;
			this->gameOver = true;
		}
	}
	if (!this->exit) {
		clrscr();
		printBoard();
		printLives();
	}
}
void General::printLives() {
	if (!this->isSilent) {
		gotoxy(MIN_X + L_Pos[currBoardNum].getPointX(), MIN_Y + L_Pos[currBoardNum].getPointY());
		cout << "Lives: " << this->game.getCurrLives();
		gotoxy(MIN_X + L_Pos[currBoardNum].getPointX(), MIN_Y + L_Pos[currBoardNum].getPointY() + 1);
		cout << "Score: " << this->game.getCurrScore();
	}
}
void General::checkLives() {
	printLives();
	if (this->game.getCurrLives() == 0) {
		this->gameOver = true;
	}

}
void General::getFileNames() {
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".txt") {
			this->fileNames.push_back(filenameStr);
		}
		if (filenameStr.substr(0, 4) == "menu" && filename.extension() == ".txt") {
			this->menuFile = filenameStr;
		}
		if (filenameStr.substr(0, 9) == "game_over" && filename.extension() == ".txt") {
			this->gameOverPrint = filenameStr;
		}
		if (filenameStr.substr(0, 10) == "user_instr" && filename.extension() == ".txt") {
			this->instructionsFile = filenameStr;
		}
		if (filenameStr.substr(0, 3) == "esc" && filename.extension() == ".txt") {
			this->escFile = filenameStr;
		}
		if (filenameStr.substr(0, 3) == "win" && filename.extension() == ".txt") {
			this->winFile = filenameStr;
		}
	}
	sort(this->fileNames.begin(), this->fileNames.end());
}
void General::uploadBoards() {
	validText boardData;
	vector<vector<char>> fileContent;
	string line;
	for (const string& fileName : this->fileNames) {
		ifstream screen_file(fileName);
		if (!screen_file.is_open()) {
			cout << "Error opening: " << fileName << endl;
			boardData.text = vector<vector<char>>();
			boardData.valid = false;
			this->boards.push_back(boardData);
			continue;
		}
		while (getline(screen_file, line)) {
			fileContent.emplace_back(line.begin(), line.end());
		}
		screen_file.close();
		if (fileContent.empty()) {
			boardData.text = fileContent;
			boardData.valid = false;
			this->boards.push_back(boardData);
			continue;
		}
		boardData.text = fileContent;
		boardData.valid = true;
		checkValidBoard(boardData);
		if (boardData.valid) {
			boardData.fileNameSteps = fileName.substr(0, 8) + ".steps";
			boardData.fileNameResults = fileName.substr(0, 8) + ".result";
		}
		this->boards.push_back(boardData);
		fileContent.clear();
	}
}
void General::checkValidBoard(validText& board) {
	bool validateInnerSize;
	Board textBoard;
	Point L_Point;
	if (!board.valid)
		return;
	else {
		textBoard.setBoard(board.text);
		validateInnerSize = checkInnerSize(board.text);
		if (board.text.size() < MIN_HEIGHT || board.text.size() > MAX_HEIGHT || !validateInnerSize)
			board.valid = false;
		board.valid = validateInnerSize && textBoard.checkCharacters(L_Point);
		this->L_Pos.push_back(L_Point);
		if (board.valid) {
			board.text = textBoard.getOriginalBoard();
		}
	}
}
bool General::checkInnerSize(const vector<vector<char>> board) {
	if (board.empty())
		return false;
	size_t expectedSize = board[0].size();
	for (size_t i = 0; i < board.size(); ++i) {
		if (board[i].size() != expectedSize)
			return false;
		if (board[i].size() < MIN_WIDTH || board[i].size() > MAX_WIDTH)
			return false;
	}
	return true;
}
void General::gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
void General::clrscr()
{
	system("cls");
}
void General::draw(char ch, Point point) {
	gotoxy(MIN_X + point.getPointX(), point.getPointY() + MIN_Y);
	cout << ch;
}
void General::printBoard() {
	if (!this->isSilent) {
		vector <vector<char>> currBoard = this->board.getCurrBoard();
		int i = 0;
		for (const auto& row : currBoard) {
			gotoxy(MIN_X, i + MIN_Y);
			for (char ch : row) {
				cout << ch;
			}
			i++;
			cout << endl;
		}
	}
}
void General::myPrint(string fileName) {
	clrscr();
	ifstream textFile(fileName);
	if (!textFile.is_open()) {
		cout << "Error opening: " << fileName << endl;
		return;
	}
	string line;
	while (getline(textFile, line)) {
		cout << line << endl;
	}
	textFile.close();
}
void General::printInstructions()
{
	clrscr();
	myPrint(this->instructionsFile);
	char ch;
	bool flag = false;
	while (!flag) {
		ch = char(_getch());
		if (ch == '3') {
			flag = true;
		}
	}
	clrscr();
	myPrint(this->menuFile);

}