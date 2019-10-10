#include <SFML\Graphics.hpp>

#include "MOO Engine.h"
#include "Game State Base.h"
#include "Major Game State Enum.h"

#include "Intro State.h"
#include "Title State.h"
#include "Main Game State.h"

#include <fstream>

int main()
{

	std::ofstream log("Main Loop Log.txt");

	log << "Creating Engine....";
	MOO::MOOEngine gameEngine;
	log << "Successful!" << std::endl;

	log << "Creating IntroState...";
	GameStateBase<MajorStates::Code>* currentState = new IntroState( &gameEngine );
	log << "Successful!" << std::endl;

	while( currentState != NULL )
	{
		log << "Attempting input...";
		currentState->HandleInput();
		log << "Successful!" << std::endl;

		log << "Attempting logic...";
		currentState->HandleLogic();
		log << "Successful!" << std::endl;

		log << "Attempting output...";
		currentState->HandleOutput();
		log << "Successful!" << std::endl;


		switch( currentState->nextState )
		{
			
			case MajorStates::Title:
			{
				delete currentState;
				currentState = NULL;
				log << "Creating Title State...";
				currentState = new TitleState( &gameEngine );
				log << "Successful!" << std::endl;

				break;
			}
		
			case MajorStates::Main:
			{
				delete currentState;
				currentState = NULL;
				log << "Creating Main Game State...";
				currentState = new MainGameState( &gameEngine );
				log << "Successful!" << std::endl;
				break;
			}
			
			case MajorStates::Quit:
			{
				delete currentState;
				currentState = NULL;
				break;
			}
		}
	}

	return 0;
}
