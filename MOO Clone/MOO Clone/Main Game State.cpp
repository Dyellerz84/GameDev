#include "Main Game State.h"

#include "Galaxy Creator.h"

MainGameState::MainGameState( MOO::MOOEngine* setEngine )
{
	engine = setEngine;

	stateStack.push( new GalaxyViewState( setEngine, &gameData ));

	log.open("MainGameLog.txt");

	gameData.galaxy = MOO::GameCreation::CreateStarSystems( GalaxySize::Large );
	
	OutputGalaxyData();

	/*if( engine->gameToLaunch.empty() )
	{
		stateStack.push( new NewGameSetupState( setEngine, &gameData ) );
	}

	else
	{
		gameData = LoadGameData( engine->gameToLaunch );
	}*/
}

MainGameState::~MainGameState()
{
	while( stateStack.empty() == false )
	{
		delete stateStack.top();
		stateStack.pop();
	}
}

void MainGameState::HandleInput()
{
	log << "Attempting to handle input...";

	stateStack.top()->HandleInput();

	log << "Successful!" << std::endl;
}

void MainGameState::HandleLogic()
{
	log << "Attempting to handle logic...";

	stateStack.top()->HandleLogic();

	log << "Successful!" << std::endl;
}
	
void MainGameState::HandleOutput()
{
	log << "Attempting to handle output...";

	std::stack<GameStateBase<MainGameStates::Code>*> drawStack;

	drawStack.push( stateStack.top() );

	stateStack.pop();

	while(drawStack.top()->fullScreen == false && stateStack.empty() == false)
	{
		drawStack.push( stateStack.top() );
		stateStack.pop();
	}
	
	engine->ClearScreen();

	while( drawStack.empty() == false )
	{
		drawStack.top()->HandleOutput();

		stateStack.push( drawStack.top() );
		drawStack.pop();
	}

	engine->DisplayScreen();

	log <<"Successful!" << std::endl;

	log <<"Attempting to determine next state...";

	DetermineNextState();

	log <<"Succesful!" << std::endl;
}

void MainGameState::DetermineNextState()
{
	switch(stateStack.top()->nextState)
	{
		case MainGameStates::Research:
		{
			stateStack.top()->nextState = MainGameStates::NoChange;

			stateStack.push( new ResearchState ( engine ) );

			break;
		}
				
		case MainGameStates::Quit:
		{
			delete stateStack.top();

			stateStack.pop();
			
			break;
		}
	}

	if(stateStack.empty())
	{
		nextState = MajorStates::Quit;
	}
}

Game::GameData MainGameState::LoadGameData( std::string )
{
	return Game::GameData();
}

void MainGameState::OutputGalaxyData()
{
	std::ofstream output("Galaxy Data.txt");

	output << "Number of Systems = " << gameData.galaxy.stars.size() << std::endl << std::endl;

	for(unsigned int i = 0; i < gameData.galaxy.stars.size(); i++)
	{
		output <<  gameData.galaxy.stars[i].name << std::endl;

		output << "Location = " << gameData.galaxy.stars[i].location.x << ", " << gameData.galaxy.stars[i].location.y << std::endl;

		output << std::endl << "     Number of planets in system = " << gameData.galaxy.stars[i].planets.size() << std::endl;

		for(unsigned int j = 0; j < gameData.galaxy.stars[i].planets.size(); j++)
		{
			output << "     Orbital position = " << gameData.galaxy.stars[i].planets[j].solarLocation << std::endl;

			output << "     Climate = " << gameData.galaxy.stars[i].planets[j].GetClimateString() << std::endl;

			output << "     Mineral Abundance = " << gameData.galaxy.stars[i].planets[j].GetMineralString() << std::endl;

			output << "     Planet Size = " << gameData.galaxy.stars[i].planets[j].GetSizeString() << std::endl;

			output << "     Base Maximum Population = " << gameData.galaxy.stars[i].planets[j].baseMaximumPopulation << std::endl;

			output << std::endl;
		}
	}
}
