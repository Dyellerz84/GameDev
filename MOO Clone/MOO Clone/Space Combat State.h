#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class SpaceCombatState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	SpaceCombatState();
	~SpaceCombatState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};