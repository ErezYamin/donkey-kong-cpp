#include "Board.h"
#include "Point.h"
void Board::setBoard(vector<vector<char>> _board) {
	this->originalBoard_ = std::move(_board);
	this->row = this->originalBoard_.size();
	this->col = this->row > 0 ? this->originalBoard_[0].size() : 0;
}
int Board::getRowBoard()const {
	return this->row;
}
int Board::getColBoard()const {
	return this->col;
}
vector<vector<char>> Board::getOriginalBoard() const {
	return this->originalBoard_;
}
vector<vector<char>> Board::getCurrBoard() const {
	return this->currBoard;
}
void Board::reset() {
	this->currBoard.resize(this->originalBoard_.size());
	for (size_t i = 0; i < this->originalBoard_.size(); ++i) {
		this->currBoard[i] = this->originalBoard_[i];
	}
}
vector <Moves> Board::characterLocation() {
	vector <Moves> characterLocV;
	Moves charLocation;
	char currCh;
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			currCh = this->currBoard[i][j];
			if (!notCharacterChar(currCh)) {
				if (currCh == GHOST_CH || currCh == MARIO_CH || currCh == SPECIAL_GHOST_CH) {
					this->currBoard[i][j] = ' ';
				}
				charLocation = { currCh, static_cast<int>(j), static_cast<int>(i) };
				characterLocV.push_back(charLocation);
			}
		}
	}
	return characterLocV;
}
bool Board::notCharacterChar(char ch) const {
	if (ch == '-' || ch == '>' || ch == '<' || ch == '=' || ch == ' ' || ch == '|' || ch == '-' || ch == LEDDER) {
		return true;
	}
	return false;
}
bool Board::checkCharacters(Point& L_point) {
	if (this->originalBoard_.empty())
		return false;
	char ch;
	bool isLegend = false, isMarioValid = false, isPaulineValid = false, isDonkeyValid = false, areGhostsValid = true, isHammerValid = false, walls = true;
	this->row = this->originalBoard_.size();
	this->col = this->originalBoard_[0].size();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			ch = this->originalBoard_[i][j];
			switch (ch)
			{
			case L_CH:
				isLegend = checkLegend(static_cast<int>(i), static_cast<int>(j));
				if (isLegend) {
					L_point.setPoint(j, i);
				}
				break;
			case MARIO_CH:
				isMarioValid = checkIfSeen(static_cast<int>(i), static_cast<int>(j), isMarioValid);
				break;
			case PAULINE_CH:
				isPaulineValid = checkCharacterSeen(static_cast<int>(i), static_cast<int>(j), isPaulineValid);
				break;
			case DONKEY_CH:
				isDonkeyValid = checkCharacterSeen(static_cast<int>(i), static_cast<int>(j), isDonkeyValid);
				break;
			case GHOST_CH || SPECIAL_GHOST_CH:
				areGhostsValid = checkCharacterSeen(static_cast<int>(i), static_cast<int>(j), false);
				break;
			case HAMMER_CH:
				isHammerValid = checkCharacterSeen(static_cast<int>(i), static_cast<int>(j), isHammerValid);
				break;
			}
		}
	}
	return isLegend && isMarioValid && isPaulineValid && areGhostsValid;
}
bool Board::checkLegend(int i, int j) {

	if (i + LEGEND_WIDTH >= this->col || j + LEGEND_HEIGHT >= this->row)
		return false;
	for (int x = i; x <= i + LEGEND_HEIGHT; ++x) {
		for (int y = j; y <= j + LEGEND_WIDTH; ++y) {
			if (this->originalBoard_[x][y] != ' ' && this->originalBoard_[x][y] != L_CH)// get char function
				return false;
		}

	}
	return true;
}
bool Board::checkIfSeen(int i, int j, int haveSeen) {
	if (haveSeen)
		this->originalBoard_[i][j] = ' ';
	return true;
}
bool Board::checkCharacterSeen(int i, int j, int haveSeen) {
	if (i + 1 >= this->row) {
		return false;
	}
	if (this->originalBoard_[i + 1][j] != '<' && this->originalBoard_[i + 1][j] != '>' && this->originalBoard_[i + 1][j] != '=' && this->originalBoard_[i + 1][j] != '-') // change to const 
		return false;
	checkIfSeen(i, j, haveSeen);
	return true;
}
