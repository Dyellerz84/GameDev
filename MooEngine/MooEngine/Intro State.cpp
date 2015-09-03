#include "Intro State.h"

IntroState::IntroState(MOO::MOOEngine* setEngine) : GameStateBase(setEngine, MajorStates::NoChange)
{
	splashImage = engine->imageManager.LoadNewImage("SplashScreen.png");

	fadeIn = true;
	fadeOut = false;

	fadeInTime = 2.0;
	pauseTime = 2.0;
	fadeOutTime = 2.0;
	
	fade = 0;
}

IntroState::~IntroState()
{
	engine->ResetAllManagers();
}

void IntroState::HandleInput() 
{
	while( engine->GetUserInput( userInput ) )
	{
		if( (userInput.type == sf::Event::KeyReleased || userInput.type == sf::Event::MouseButtonReleased) && fadeOut == false)
		{
			fadeIn = false;
			fadeOut = true;
			
			fadeTimer.restart();
		}
	}
}

void IntroState::HandleLogic()
{
	if( fadeIn == true )
	{
		if( fade >= 1 )
		{
			fade = 1;

			fadeIn = false;

			splashImage.setColor( sf::Color( 255, 255, 255, 255 ) );

			fadeTimer.restart();
		}

		else
		{
			fade += fadeTimer.restart().asSeconds() / fadeInTime; 

			splashImage.setColor( sf::Color(255,255,255, 255 * fade) );
		}
	}

	else if( fadeOut == false )
	{
		if( fadeTimer.getElapsedTime().asSeconds() >= pauseTime )
		{
			fadeOut = true;

			fadeTimer.restart();
		}
	}

	else if( fadeOut == true )
	{
		fade -= fadeTimer.restart().asSeconds() / fadeOutTime;

		splashImage.setColor( sf::Color( 255, 255, 255, 255 * fade ) );

		if( fade <= 0 )
		{
			nextState = MajorStates::Title;
		}		
	}
}

void IntroState::HandleOutput()
{
	engine->ClearScreen();
	engine->Draw( splashImage );
	engine->DisplayScreen();
}