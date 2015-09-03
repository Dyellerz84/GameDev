#include "Galaxy Setup State.h"
#include "New Game Setup State Enum.h"

GalaxySetupState::GalaxySetupState( MOO::MOOEngine* setEngine, NewGameSettingsData* setData ) : GameStateBase( setEngine, NewGameSetupStates::NoChange )
{
	newGameSettingsData = setData;
}

GalaxySetupState::~GalaxySetupState()
{

}

void GalaxySetupState::HandleInput()
{

}

void GalaxySetupState::HandleLogic()
{

}

void GalaxySetupState::HandleOutput()
{

}