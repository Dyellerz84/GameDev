#include "Main Title State.h"

MainTitleState::MainTitleState( MOO::MOOEngine* setEngine ) : GameStateBase ( setEngine, TitleStates::NoChange )
{
	fullScreen = true;

	mouseClicked = false;
	mouseReleased = false;

	CreateUI();

	log.open("log.txt");

	backgroundImage = engine->imageManager.LoadNewImage("Resources/Title State/MenuBackground.png");
}

MainTitleState::~MainTitleState()
{
	
}

void MainTitleState::HandleInput()
{
	mouseReleased = false;
		
	HandleUserInput();
	HandleGameEvents();
}

void MainTitleState::HandleLogic()
{
	ui.CheckMouse( engine->GetMousePostion(), mouseClicked, mouseReleased );
}

void MainTitleState::HandleOutput()
{
	engine->Draw( backgroundImage );

	std::vector<sf::Sprite> buttonSprites = ui.GetSprites();
	
	for(unsigned int i = 0; i < buttonSprites.size(); i++)
	{
		engine->Draw( buttonSprites[i] );
	}
}

void MainTitleState::HandleUserInput()
{
	while( engine->GetUserInput( userInput ) )
	{
		switch( userInput.type )
		{
			case sf::Event::KeyReleased:
			{
				switch( userInput.key.code )
				{
					case sf::Keyboard::A:
					{
						nextState = TitleStates::Settings;	

						break;
					}

					case sf::Keyboard::S:
					{
						nextState = TitleStates::LoadGame;

						break;
					}

					case sf::Keyboard::D:
					{
						nextState = TitleStates::Credits;

						break;
					}

					case sf::Keyboard::F:
					{
						nextState = TitleStates::Quit;

						break;
					}
				}

				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				switch ( userInput.mouseButton.button )
				{
					case sf::Mouse::Left:
					{
						mouseClicked = true;
						
						break;
					}
				}
				
				break;
			}

			case sf::Event::MouseButtonReleased:
			{
				switch ( userInput.mouseButton.button )
				{
					case sf::Mouse::Left:
					{
						mouseClicked = false;
						mouseReleased = true;

						break;
					}
				}

				break;
			}
		}
	}
}

void MainTitleState::HandleGameEvents()
{
	MainTitleStateEvents::Event gameEvent;

	while( eventQueue.PollEvents( gameEvent ) )
	{
		log << "Polling Events" << std::endl;

		switch( gameEvent )
		{
			case MainTitleStateEvents::StartNewGame:
			{
				nextState = TitleStates::NewGame;
				
				break;
			}

			case MainTitleStateEvents::Continue:
			{
				nextState = TitleStates::Continue;

				break;
			}

			case MainTitleStateEvents::LoadGame:
			{
				nextState = TitleStates::LoadGame;

				break;
			}

			case MainTitleStateEvents::GoToSettings:
			{
				nextState = TitleStates::Settings;

				break;
			}

			case MainTitleStateEvents::GoToCredits:
			{
				nextState = TitleStates::Credits;

				break;
			}

			case MainTitleStateEvents::Quit:
			{
				nextState = TitleStates::Quit;

				break;
			}
		}
	}
}

void MainTitleState::CreateUI()
{
	ui.SetEventSystem( &eventQueue );

	sf::Rect<unsigned short int> buttonShape( MOO::Globals::gameWidth / 2 - 125, MOO::Globals::gameHeight / 2 - 150, 250, 100  );
	sf::Sprite buttonSprite = engine->imageManager.LoadNewImage("Resources/Title State/NewGameButtonImage.png");
	sf::Sound buttonSound = engine->soundManager.LoadNewSound("Resources/Title State/ButtonSound.wav");

	MainTitleStateEvents::Event buttonEvent = MainTitleStateEvents::StartNewGame;

	ui.AddButton( new MOO::UI::Buttons::EventButton<MainTitleStateEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, buttonSprite, buttonSound, buttonEvent, sf::Vector2f(buttonShape.left, buttonShape.top) ) );

	buttonShape.top += 100;
	buttonEvent = MainTitleStateEvents::Continue;
	buttonSprite = engine->imageManager.LoadNewImage("Resources/Title State/ContinueButtonImage.png");
	
	ui.AddButton( new MOO::UI::Buttons::EventButton<MainTitleStateEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Disabled, buttonSprite, buttonSound, buttonEvent, sf::Vector2f(buttonShape.left, buttonShape.top)) );

	buttonShape.top += 100;
	buttonEvent = MainTitleStateEvents::LoadGame;
	buttonSprite = engine->imageManager.LoadNewImage("Resources/Title State/LoadGameButton.png");

	ui.AddButton( new MOO::UI::Buttons::EventButton<MainTitleStateEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Disabled, buttonSprite, buttonSound, buttonEvent, sf::Vector2f(buttonShape.left, buttonShape.top)) );

	buttonShape.top += 100;
	buttonEvent = MainTitleStateEvents::GoToSettings;
	buttonSprite = engine->imageManager.LoadNewImage("Resources/Title State/SettingsButton.png");
	
	ui.AddButton( new MOO::UI::Buttons::EventButton<MainTitleStateEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, buttonSprite, buttonSound, buttonEvent, sf::Vector2f(buttonShape.left, buttonShape.top)) );

	buttonShape.top += 100;
	buttonEvent = MainTitleStateEvents::GoToCredits;
	buttonSprite = engine->imageManager.LoadNewImage("Resources/Title State/CreditsButton.png");

	ui.AddButton( new MOO::UI::Buttons::EventButton<MainTitleStateEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, buttonSprite, buttonSound, buttonEvent, sf::Vector2f(buttonShape.left, buttonShape.top)) );

	buttonShape.top += 100;
	buttonEvent = MainTitleStateEvents::Quit;
	buttonSprite = engine->imageManager.LoadNewImage("Resources/Title State/QuitButton.png");

	ui.AddButton( new MOO::UI::Buttons::EventButton<MainTitleStateEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, buttonSprite, buttonSound, buttonEvent, sf::Vector2f(buttonShape.left, buttonShape.top)) );	
}