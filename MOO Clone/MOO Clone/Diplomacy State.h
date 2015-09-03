#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class DiplomacyState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	DiplomacyState();
	~DiplomacyState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};