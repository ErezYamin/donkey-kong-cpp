#include "LoadMode.h"
#include "GameMode.h"
#include "General.h"
void LoadMode::currMode() {
	bool valid = this->checkFilesBoard();
	if (!valid) {
		cout << "can't open results/step file";
		general.clrscr();
		general.myPrint(general.gameOverPrint);
		return;
	}
	general.GameOn();
}
char LoadMode::getCharGameMode() const {
	return general.steps.popStep();
}
void LoadMode::initGameMode() {
	this->general.steps = Steps::loadSteps(this->general.boards[general.currBoardNum].fileNameSteps);
	this->general.randomSeed = general.steps.getRandomSeed();
	this->general.results = Results::loadResults(this->general.boards[general.currBoardNum].fileNameResults);
	this->general.gen.seed(this->general.randomSeed);
}
int LoadMode::displayBoards() {
	bool valid = false;
	for (size_t i = 0; i < this->general.boards.size(); i++) {
		if (this->general.boards[i].valid) { return i; }
	}
}
bool LoadMode::checkKB(size_t iteration) {
	if (general.steps.isNextStepOnIteration(iteration)) {
		return true;
	}
	return false;
}
void LoadMode::handleVectorResultsAndSteps() {
	general.clrscr();
	if (this->general.winGame) {
		if (general.results.popResult() != general.pair) {
			general.unmatchingResultFile = true;
			cout << "Actual result does not corresponds to the expected win result";
		}
		else {
			if (general.results.popResult() != general.scorePair) { cout << "Actual result does not corresponds to the expected score result"; }
			else {
				cout << "Actual result corresponds to the expected result";
			}
		}
	}
	else if (this->general.unmatchingResultFile) {
		cout << "Actual result does not corresponds to the expected lose life result";
	}
	else {
		cout << "Actual result corresponds to the expected lose life result";
	}
	Sleep(800);
}