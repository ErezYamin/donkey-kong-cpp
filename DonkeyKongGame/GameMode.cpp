#include "GameMode.h"
#include "General.h"
bool GameMode::checkFilesBoard() {
	bool valid = false;
	for (size_t i = 0; i < this->general.boards.size(); i++) {
		valid = this->general.chooseBoard(i);
		if (!valid && this->general.boards[i].valid) {
			this->general.boards[i].valid = false;
			return false;
		}
	}
	return true;
}