#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class FleetsOverviewState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	FleetsOverviewState();
	~FleetsOverviewState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};