#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class ColonyOverviewState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	ColonyOverviewState();
	~ColonyOverviewState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};