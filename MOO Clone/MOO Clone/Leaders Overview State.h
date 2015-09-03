#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class LeadersOverviewState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	LeadersOverviewState();
	~LeadersOverviewState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};