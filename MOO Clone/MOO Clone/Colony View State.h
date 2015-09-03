#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class ColonyViewState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	ColonyViewState();
	~ColonyViewState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};