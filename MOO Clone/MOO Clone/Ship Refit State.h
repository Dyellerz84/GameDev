#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class ShipRefitState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	ShipRefitState();
	~ShipRefitState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};