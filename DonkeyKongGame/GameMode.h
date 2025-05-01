#pragma once
//#include "General.h"
class General;
class GameMode
{
protected:
	General& general;
public:
	GameMode(General& _general) : general(_general) {}
	virtual void currMode() = 0;
	virtual char getCharGameMode() const = 0;
	virtual void initGameMode() = 0;
	virtual int displayBoards() = 0;
	virtual bool checkKB(size_t iteration) = 0;
	virtual void handleVectorResultsAndSteps() = 0;
	bool checkFilesBoard();


};
