#pragma once

#include "Game State Base.h"
#include "New Game Setup State Enum.h"
#include "UI.h"
#include "Civilization Setup States Enum.h"

class CivilizationSetupState : public GameStateBase<NewGameSetupStates::State>
{

private:

	MOO::UI::UI<CivilizationSetupEvents::Event> ui;

	void CreateUI();

public:

	CivilizationSetupState( MOO::MOOEngine* setEngine, CivilizationData* playerCivilization );
	~CivilizationSetupState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};