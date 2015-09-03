#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class EncyclopediaState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	EncyclopediaState();
	~EncyclopediaState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};