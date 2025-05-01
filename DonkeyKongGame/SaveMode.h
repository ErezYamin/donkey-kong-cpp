#pragma once
#include "GameMode.h"
class SaveMode : public GameMode
{
	bool isSave;
private:
	char input;
public:
	SaveMode(General& gen, bool _isSave) : GameMode(gen), isSave(_isSave) {}
	virtual void currMode() override;
	virtual char getCharGameMode() const override;
	virtual void initGameMode()override;
	virtual int displayBoards()override;
	virtual void handleVectorResultsAndSteps() override;
	virtual bool checkKB(size_t iteration) override;
	void userChoice();
};
