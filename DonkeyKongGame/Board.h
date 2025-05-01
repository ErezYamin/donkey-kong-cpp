#pragma once
#include "Settings.h"
#include "windowsUtils.h"
#include "Point.h"
class Board
{
	vector <vector<char>> originalBoard_;
	vector<vector<char>> currBoard;
private:
	int row = 0;
	int col = 0;
public:
	Board() {}
	void setBoard(vector<vector<char>> _board);
	int getRowBoard()const;
	int getColBoard()const;
	vector<vector<char>> getOriginalBoard() const;
	vector<vector<char>> getCurrBoard() const;
	bool notCharacterChar(char ch)const;
	void reset();
	vector <Moves> characterLocation();
	bool checkCharacters(Point& L_point);
	bool checkLegend(int i, int j);
	bool checkIfSeen(int i, int j, int haveSeen);
	bool checkCharacterSeen(int i, int j, int haveSeen);
	char getChar(int x, int y) const {
		if ((x > this->col || x < 0) || (y >= this->row) || y < 0)
		{
			return '-1';
		}
		else {
			return currBoard[y][x];
		}
	}
};
