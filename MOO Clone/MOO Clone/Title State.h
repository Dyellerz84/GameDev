#pragma once

#include <stack>

#include <fstream>


#include "Game State Base.h"
#include "Major Game State Enum.h"

#include "Title States Compilation.h"
#include "Title States Enum.h"

class TitleState : public GameStateBase<MajorStates::Code>
{

private: //data
	
	std::ofstream log;

	std::stack<GameStateBase<TitleStates::Code>*> stateStack;

	GameStateBase<TitleStates::Code>* mainTitleState;
	GameStateBase<TitleStates::Code>* creditsState;
	GameStateBase<TitleStates::Code>* loadGameState;
	GameStateBase<TitleStates::Code>* settingsState;

private: //functions

	void RenderScreen();
	void DetermineNextState();

public:

	TitleState( MOO::MOOEngine* setEngine );
	~TitleState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};