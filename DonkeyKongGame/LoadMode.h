#pragma once
#include "GameMode.h"
//class GameMode;
class LoadMode : public GameMode
{
	bool isSilent;
public:
	LoadMode(General& gen, bool _isSilent) : GameMode(gen), isSilent(_isSilent) {}
	virtual void currMode() override;
	virtual char getCharGameMode()const override;
	virtual void initGameMode()override;
	virtual int displayBoards()override;
	virtual void handleVectorResultsAndSteps() override;
	virtual bool checkKB(size_t iteration) override;


};
