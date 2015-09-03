#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class ColonyBuildQueueState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	ColonyBuildQueueState();
	~ColonyBuildQueueState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};