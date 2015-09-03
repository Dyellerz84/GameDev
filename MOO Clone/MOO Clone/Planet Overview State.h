#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class PlanetsOverviewState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	PlanetsOverviewState();
	~PlanetsOverviewState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};