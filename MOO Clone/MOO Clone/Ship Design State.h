#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"

class ShipDesignState : public GameStateBase<MainGameStates::Code>
{

private:

public:

	ShipDesignState();
	~ShipDesignState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};