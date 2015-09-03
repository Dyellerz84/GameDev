#pragma once

#include "Game State Base.h"
#include "New Game Settings Data.h"
#include "New Game Setup State Enum.h"
#include "UI.h"
#include "Game Event System.h"

namespace GalaxySetupEvents
{
	enum Event{ Close };
}

class GalaxySetupState : public GameStateBase<NewGameSetupStates::State>
{

private:

	MOO::UI::UI<GalaxySetupEvents::Event> ui;

	NewGameSettingsData* newGameSettingsData;

	void CreatUI();

public:

	GalaxySetupState( MOO::MOOEngine* setEngine, NewGameSettingsData* setData );
	~GalaxySetupState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};