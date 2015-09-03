#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class PlanetaryCombatState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	PlanetaryCombatState();
	~PlanetaryCombatState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};