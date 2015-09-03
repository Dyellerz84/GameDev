#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class PlanetaryBombardmentState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	PlanetaryBombardmentState();
	~PlanetaryBombardmentState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};