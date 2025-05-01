#include "SaveMode.h"
#include "GameMode.h"
#include "General.h"
bool SaveMode::checkKB(size_t iteration) {
	if (_kbhit()) {
		return true;
	}
}
void SaveMode::currMode() {
	this->general.myPrint(general.menuFile);
	this->input = char(_getch());
	userChoice();
}
void SaveMode::userChoice() {
	while (this->input != '1' && !this->general.exit) {
		switch (input)
		{
		case '8':
			this->general.printInstructions();
			input = _getch();
			break;
		case '9':
			this->general.clrscr();
			this->general.myPrint(this->general.gameOverPrint);
			Sleep(200);
			this->general.exit = true;
			break;
		default:
			input = char(_getch());
			break;
		}
	}
	if (input == '1') {
		this->general.clrscr();
		this->general.GameOn();
	}
}
char SaveMode::getCharGameMode()const {
	return char(_getch());
}
void SaveMode::initGameMode() {
	this->general.steps.clearSteps();
	this->general.results.clearResults();
	long randomSeed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	general.gen.seed(randomSeed);
	general.steps.setRandomSeed(randomSeed);
	general.game.setRandomGenerator(general.gen);
}
int SaveMode::displayBoards() {
	bool valid = false;
	bool filesMovesValid = true;
	int invalidBoard = 0;
	while (!valid) {
		for (size_t i = 0; i < this->general.fileNames.size(); ++i) {
			cout << (i + 1) << ": " << this->general.fileNames[i] << endl;
			if (!this->general.boards[i].valid) { invalidBoard++; }
			else { invalidBoard = 0; }
		}
		if (invalidBoard == this->general.boards.size() || !checkFilesBoard()) {
			cout << "All boards are invalid, Good bye! ";
			input = -1;
			valid = true;
			Sleep(550);
			general.clrscr();
			general.myPrint(this->general.gameOverPrint);
			Sleep(150);
		}
		else
		{
			input = int(_getch() - '1');
			valid = general.chooseBoard(input);
		}
		Sleep(450);
		general.clrscr();
	}
	return input;
}
void SaveMode::handleVectorResultsAndSteps() {
	if (isSave) {
		general.steps.saveSteps(this->general.boards[general.currBoardNum].fileNameSteps);
		general.results.saveResults(this->general.boards[general.currBoardNum].fileNameResults);
	}
}