#pragma once

#include "Game State Base.h"
#include "Title States Enum.h"

class LoadGameState : public GameStateBase<TitleStates::Code>
{

private:

public:

	LoadGameState( MOO::MOOEngine* setEngine );
	~LoadGameState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();

};