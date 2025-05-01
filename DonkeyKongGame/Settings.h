#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <conio.h>
#include "windowsUtils.h"
using namespace std;
static constexpr int BOARD_GAME_WIDTH = 80;
static constexpr int BOARD_GAME_HEIGHT = 25;
static constexpr int MIN_HEIGHT = 20;
static constexpr int MAX_HEIGHT = 30;
static constexpr int MIN_WIDTH = 60;
static constexpr int MAX_WIDTH = 100;
static constexpr int LEGEND_WIDTH = 20;
static constexpr int LEGEND_HEIGHT = 3;
static constexpr int MIN_Y = 2;
static constexpr int MIN_X = 20;
static constexpr int ESC = 27;
const int PROABILITY_TO_BARREL = 10;
const int PROABILITY_TO_GHOST_CHANGE_DIR = 5;
const int PROABILITY_TO_GHOST_CLIMB = 15;
const int NUM_OFF_MARIO_FALL_MOVES = 5;
const int NUM_OFF_BARREL_FALL_MOVES = 8;
static int RADIUS = 2;
const char LEDDER = 'H';
const char BARREL_CH = 'O';
const char MARIO_CH = '@';
const char DONKEY_CH = '&';
const char PAULINE_CH = '$';
const char L_CH = 'L';
const char HAMMER_CH = 'p';
const char GHOST_CH = 'x';
const char SPECIAL_GHOST_CH = 'X';
enum class eDirection { LEFT = 'a', RIGHT = 'd', STAY = 's', UP = 'w', DOWN = 'x', ESC = 27 };
struct Moves {
	char ch;
	int x, y;
};
struct validText {
	vector<vector<char>> text;
	string fileNameSteps;
	string fileNameResults;
	bool valid;
	bool used = false;
};
//static random_device rd;
//static mt19937 gen(rd());
//static uniform_int_distribution<> dist(1, 100);