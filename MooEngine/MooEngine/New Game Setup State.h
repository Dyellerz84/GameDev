#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"
#include "New Game Setup State Enum.h"
#include "Game Data.h"
#include "New Game Settings Data.h"

class NewGameSetupState : public GameStateBase<MainGameStates::Code>
{

private:

	GameStateBase<NewGameSetupStates::State>* currentState;

	NewGameSettingsData newGameSettings;

	Game::GameData* gameData;

public:

	NewGameSetupState( MOO::MOOEngine* setEngine, Game::GameData* setData );
	~NewGameSetupState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};