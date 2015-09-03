#include "Title State.h"

TitleState::TitleState( MOO::MOOEngine* setEngine ) : GameStateBase( setEngine, MajorStates::NoChange )
{
	mainTitleState = new MainTitleState( setEngine );
	creditsState = new CreditsState( setEngine );
	loadGameState = new LoadGameState( setEngine );
	settingsState = new SettingsState( setEngine );

	stateStack.push( mainTitleState );
}

TitleState::~TitleState()
{
	delete mainTitleState;
	delete creditsState;
	delete loadGameState;
	delete settingsState;
}

void TitleState::HandleInput()
{
	stateStack.top()->HandleInput();
}

void TitleState::HandleLogic()
{
	stateStack.top()->HandleLogic();
}

void TitleState::HandleOutput()
{
	RenderScreen();

	DetermineNextState();
}

void TitleState::RenderScreen()
{
	std::stack<GameStateBase<TitleStates::Code>*> drawStack;

	drawStack.push( stateStack.top() );

	while(stateStack.top()->fullScreen == false && stateStack.empty() == false)
	{
		stateStack.pop();
		drawStack.push( stateStack.top() );
	}

	stateStack.pop();
	
	engine->ClearScreen();

	while( drawStack.empty() == false )
	{
		drawStack.top()->HandleOutput();

		stateStack.push( drawStack.top() );
		drawStack.pop();
	}

	engine->DisplayScreen();
}

void TitleState::DetermineNextState()
{
	switch(stateStack.top()->nextState)
	{
		case TitleStates::LoadGame:
		{
			stateStack.top()->nextState = TitleStates::NoChange;

			stateStack.push( loadGameState );

			break;
		}

		case TitleStates::Settings:
		{
			stateStack.top()->nextState = TitleStates::NoChange;

			stateStack.push( settingsState );

			break;
		}

		case TitleStates::Credits:
		{
			stateStack.top()->nextState = TitleStates::NoChange;

			stateStack.push( creditsState );

			break;
		}

		case TitleStates::Quit:
		{
			stateStack.top()->nextState = TitleStates::NoChange;

			stateStack.pop();
			
			break;
		}

		case TitleStates::NewGame:
		{
			nextState = MajorStates::Main;
						
			break;
		}
	}

	if(stateStack.empty())
	{
		nextState = MajorStates::Quit;
	}
}