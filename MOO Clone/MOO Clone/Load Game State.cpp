#include "Load Game State.h"

LoadGameState::LoadGameState( MOO::MOOEngine* setEngine ) : GameStateBase ( setEngine, TitleStates::NoChange )
{
	fullScreen = false;
}

LoadGameState::~LoadGameState()
{

}

void LoadGameState::HandleInput()
{
	while( engine->GetUserInput( userInput ) )
	{
		if( userInput.type == sf::Event::KeyReleased || userInput.type == sf::Event::MouseButtonReleased )
		{
			nextState = TitleStates::Quit;
		}
	}
}

void LoadGameState::HandleLogic()
{

}

void LoadGameState::HandleOutput()
{
	sf::RectangleShape shape( sf::Vector2f( 100, 100 ));

	shape.setFillColor( sf::Color(0, 255, 0) );
	shape.setPosition( MOO::Globals::gameWidth / 2 - 50, MOO::Globals::gameHeight / 2 - 50 );

	engine->Draw(shape);
}