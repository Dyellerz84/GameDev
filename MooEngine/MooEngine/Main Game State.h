#pragma once

#include <stack>
#include <fstream>

#include "Game State Base.h"

#include "Major Game State Enum.h"
#include "Main Game States Enum.h"
#include "Main Game State Compilation.h"
#include "Main Game Events Enum.h"

#include "Game Data.h"

#include "UI.h"

class MainGameState : public GameStateBase<MajorStates::Code>
{

private: //data
		
	std::stack<GameStateBase<MainGameStates::Code>*> stateStack;

	Game::GameData gameData;

	MOO::UI::UI<MainGameEvents::Event> ui;

	std::ofstream log;

private: //function

	Game::GameData LoadGameData( std::string );

	void DetermineNextState();

	void OutputGalaxyData();

	void DeterminePlayerHome();

	void SetupStartingColonies();
	void SetupStartingFleet();

	void RunTurnUpdates();
	void UpdateStarSystems();
	void UpdateEmpires();

public:

	MainGameState( MOO::MOOEngine* setEngine );
	~MainGameState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};