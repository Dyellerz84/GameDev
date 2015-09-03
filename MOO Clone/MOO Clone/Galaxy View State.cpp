#include "Galaxy View State.h"
#include <sstream>

GalaxyViewState::GalaxyViewState(MOO::MOOEngine* setEngine, Game::GameData* setGameData) : GameStateBase( setEngine, MainGameStates::NoChange )
{
	gameData = setGameData;

	CreateUI();

	log.open("galaxyview.txt");

	log << "LOG OPEN! WE ARE IN THE GALAXYVIEWSTATE!" << std::endl;

	fullScreen = true;
	mouseClicked = false;
	mouseReleased = false;

	zoomFactor = 1;

	LoadImages();
	
	xCamera = 0;
	yCamera = 0;

	previousMousex = 0;
	previousMousey = 0;

	panningCamera = false;

	systemBeingViewed = NULL;
	systemViewState = NULL;

	gameFont.loadFromFile("cour.ttf");
}

GalaxyViewState::~GalaxyViewState()
{

}

void GalaxyViewState::HandleInput()
{
	if(systemBeingViewed != NULL)
	{
		if(systemViewState == NULL)
		{
			systemViewState = new SystemViewState( engine, systemBeingViewed );
		}
		
		if( systemViewState != NULL )
		{
			systemViewState->HandleInput();
		}
	}

	if(systemBeingViewed == NULL)
	{
		HandleGameEvents();
		HandleSystemEvents();
	}
}

void GalaxyViewState::HandleLogic()
{
	if(systemViewState == NULL)
	{
		ui.CheckMouse( engine->GetMousePostion(), mouseClicked, mouseReleased );

		if( mouseReleased == true)
		{
			CheckStarClick( engine->GetMousePostion() );
		}
	}

	else if(systemViewState != NULL)
	{
		systemViewState->HandleLogic();
	}
	
}

void GalaxyViewState::HandleOutput()
{
	log << "Beginning to draw sprites" << std::endl;

	if(systemViewState == NULL)
	{
		DrawGalaxy();

		std::vector<sf::Sprite> temp;

		temp = ui.GetSprites();

		log << temp.size() << std::endl;

		for(unsigned int i = 0; i < temp.size(); i++)
		{
			engine->Draw( temp[i] );
		}
	
		log << "Sprites Drawn" << std::endl;
	}

	else if(systemViewState != NULL)
	{
		systemViewState->HandleOutput();
		if(systemViewState->nextState == MainGameStates::Quit)
		{
			delete systemViewState;
			systemViewState = NULL;
			systemBeingViewed = NULL;
		}
	}
}

void GalaxyViewState::CreateUI()
{
	//research button

	ui.SetEventSystem( &gameEvents );

	sf::Rect<unsigned short int> buttonShape( 1430, 800, 200, 50 );
	sf::Sprite buttonImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/ResearchButton.png" );
	sf::Sound buttonSound = engine->soundManager.LoadNewSound( "Resources/Title State/ButtonSound.wav" );

	ui.AddButton(new MOO::UI::Buttons::EventButton<GalaxyViewStateEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, buttonImage, buttonSound, GalaxyViewStateEvents::GotoResearch, sf::Vector2f( 1430, 800 ) ) );
}

void GalaxyViewState::HandleGameEvents()
{
	GalaxyViewStateEvents::Event gameEvent;

	while( gameEvents.PollEvents( gameEvent ) )
	{
		switch( gameEvent )
		{
			case GalaxyViewStateEvents::GotoResearch:
			{
				nextState = MainGameStates::Research;

				break;
			}
		}
	}
}

void GalaxyViewState::DrawStars()
{
	for(unsigned int i = 0; i < gameData->galaxy.stars.size(); i++)
	{
		unsigned int screenXCenter = (MOO::Globals::gameWidth / 2);
		unsigned int screenYCenter = (MOO::Globals::gameHeight / 2);

		unsigned int galaxyXCenter = gameData->galaxy.radius / 2;
		unsigned int galaxyYCenter = gameData->galaxy.radius / 2;
		
		unsigned int centeringAdjustmentX = screenXCenter / zoomFactor - galaxyXCenter;
		unsigned int centeringAdjustmentY = screenYCenter / zoomFactor - galaxyYCenter;

		unsigned int starX = (centeringAdjustmentX + gameData->galaxy.stars[i].location.x) - xCamera;
		unsigned int starY = (centeringAdjustmentY + gameData->galaxy.stars[i].location.y) - yCamera;

		switch( gameData->galaxy.stars[i].starType )
		{
			case StarType::O:
			{
				galaxyImages.OStarImage.setPosition( starX, starY );

				engine->Draw( galaxyImages.OStarImage );

				break;
			}

			case StarType::A:
			{
				galaxyImages.AStarImage.setPosition( starX, starY );

				engine->Draw( galaxyImages.AStarImage );

				break;
			}

			case StarType::B:
			{
				galaxyImages.BStarImage.setPosition( starX, starY );

				engine->Draw( galaxyImages.BStarImage );

				break;
			}

			case StarType::F:
			{
				galaxyImages.FStarImage.setPosition( starX, starY );

				engine->Draw( galaxyImages.FStarImage );

				break;
			}

			case StarType::G:
			{
				galaxyImages.GStarImage.setPosition( starX, starY );

				engine->Draw( galaxyImages.GStarImage );

				break;
			}

			case StarType::K:
			{
				galaxyImages.KStarImage.setPosition( starX, starY );

				engine->Draw( galaxyImages.KStarImage );

				break;
			}

			case StarType::M:
			{
				galaxyImages.MStarImage.setPosition( starX, starY );

				engine->Draw( galaxyImages.MStarImage );

				break;
			}
		}
	}
}

void GalaxyViewState::DrawGalaxy()
{
	log << "Zoom Factor = " << zoomFactor << std::endl;

	


	engine->SetZoomFactor( zoomFactor );
	engine->TurnZoomOn();
	

	DrawAnomalies();
	DrawStars();

	engine->TurnZoomOff();

	std::stringstream ZFString;

	ZFString << zoomFactor;

	std::string temp( ZFString.str() );

	sf::Text zoomFactorText;

	zoomFactorText.setString( temp );
	zoomFactorText.setPosition( 0,0 );
	zoomFactorText.setColor( sf::Color(255,255,255) );
	zoomFactorText.setCharacterSize( 30 );
	zoomFactorText.setFont( gameFont );
	
	engine->Draw( zoomFactorText );

	std::stringstream cameraxstring;
	
	cameraxstring << "CameraX = " << xCamera;
	zoomFactorText.move(0, zoomFactorText.getGlobalBounds().height );
	zoomFactorText.setString(cameraxstring.str() );

	engine->Draw( zoomFactorText );
	
	std::stringstream cameraystring;

	ZFString.clear();
	cameraystring << "CameraY = " << yCamera;
	zoomFactorText.move(0, zoomFactorText.getGlobalBounds().height );
	zoomFactorText.setString(cameraystring.str() );
	engine->Draw( zoomFactorText );
}

void GalaxyViewState::HandleSystemEvents()
{
	mouseReleased = false;
	
	if( panningCamera )
	{
		int currentMouseX = sf::Mouse::getPosition().x;
		int currentMouseY = sf::Mouse::getPosition().y;

		if( previousMousex != currentMouseX )
		{
			xCamera += (previousMousex - currentMouseX) / zoomFactor;
			
			previousMousex = currentMouseX;
		}
		
		if( previousMousey != currentMouseY )
		{
			yCamera += (previousMousey - currentMouseY) / zoomFactor;

			previousMousey = currentMouseY;
		}		
	}

	while(engine->GetUserInput( userInput ) )
	{
		switch( userInput.type )
		{
			case sf::Event::KeyReleased:
			{
				HandleKeyReleases();

				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				HandleMouseButtonPresses();

				break;
			}

			case sf::Event::MouseButtonReleased:
			{
				HandleMouseButtonReleases();

				break;
			}

			case sf::Event::MouseWheelMoved:
			{
				HandleMouseWheel();

				break;
			}
		}
	}
}

void GalaxyViewState::DrawAnomalies()
{

}

void  GalaxyViewState::HandleKeyPresses()
{

}

void  GalaxyViewState::HandleKeyReleases()
{
	switch( userInput.key.code )
	{
		case sf::Keyboard::Escape:
		{
			nextState = MainGameStates::Quit;

			break;
		}

		case sf::Keyboard::R:
		{
			nextState = MainGameStates::Research;

			break;
		}
	}
}

void  GalaxyViewState::HandleMouseButtonPresses()
{
	switch( userInput.mouseButton.button )
	{
		case sf::Mouse::Left:
		{
			mouseClicked = true;

			break;
		}

		case sf::Mouse::Middle:
		{
			panningCamera = true;

			previousMousex = sf::Mouse::getPosition().x;
			previousMousey = sf::Mouse::getPosition().y;

			break;
		}

	}
}

void  GalaxyViewState::HandleMouseButtonReleases()
{
	switch( userInput.mouseButton.button )
	{
		case sf::Mouse::Left:
		{
			mouseClicked = false;
			mouseReleased = true;

			break;
		}

		case sf::Mouse::Middle:
		{
			panningCamera = false;

			break;
		}
	}
}

void  GalaxyViewState::HandleMouseWheel()
{
	zoomFactor += userInput.mouseWheel.delta * -0.1;
}

void GalaxyViewState::LoadImages()
{
	galaxyImages.OStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/O Star.png" );
	galaxyImages.OStarImage.setOrigin( galaxyImages.OStarImage.getGlobalBounds().width / 2, galaxyImages.OStarImage.getGlobalBounds().height / 2 );

	galaxyImages.BStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/B Star.png" );
	galaxyImages.BStarImage.setOrigin( galaxyImages.BStarImage.getGlobalBounds().width / 2, galaxyImages.BStarImage.getGlobalBounds().height / 2 );

	galaxyImages.AStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/A Star.png" );
	galaxyImages.AStarImage.setOrigin( galaxyImages.AStarImage.getGlobalBounds().width / 2, galaxyImages.AStarImage.getGlobalBounds().height / 2 );

	galaxyImages.FStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/F Star.png" );
	galaxyImages.FStarImage.setOrigin( galaxyImages.FStarImage.getGlobalBounds().width / 2, galaxyImages.FStarImage.getGlobalBounds().height / 2 );

	galaxyImages.GStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/G Star.png" );
	galaxyImages.GStarImage.setOrigin( galaxyImages.GStarImage.getGlobalBounds().width / 2, galaxyImages.GStarImage.getGlobalBounds().height / 2 );

	galaxyImages.KStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/K Star.png" );
	galaxyImages.KStarImage.setOrigin( galaxyImages.KStarImage.getGlobalBounds().width / 2, galaxyImages.KStarImage.getGlobalBounds().height / 2 );

	galaxyImages.MStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/M Star.png" );
	galaxyImages.MStarImage.setOrigin( galaxyImages.MStarImage.getGlobalBounds().width / 2, galaxyImages.MStarImage.getGlobalBounds().height / 2 );
}

void GalaxyViewState::CheckStarClick( sf::Vector2f mousePosition )
{
	unsigned int screenXCenter = (MOO::Globals::gameWidth / 2);
	unsigned int screenYCenter = (MOO::Globals::gameHeight / 2);

	unsigned int galaxyXCenter = gameData->galaxy.radius / 2;
	unsigned int galaxyYCenter = gameData->galaxy.radius / 2;
		
	unsigned int centeringAdjustmentX = screenXCenter / zoomFactor - galaxyXCenter;
	unsigned int centeringAdjustmentY = screenYCenter / zoomFactor - galaxyYCenter;
		
	for(unsigned int i = 0; i < gameData->galaxy.stars.size(); i++)
	{
		unsigned int xDistance = mousePosition.x - ((centeringAdjustmentX + gameData->galaxy.stars[i].location.x) - xCamera) * zoomFactor;
		unsigned int yDistance = mousePosition.y - ((centeringAdjustmentY + gameData->galaxy.stars[i].location.y) - yCamera) * zoomFactor;

		if( xDistance * xDistance + yDistance * yDistance <= ( 625 * zoomFactor ) )
		{
			systemBeingViewed = &gameData->galaxy.stars[i];

			i = gameData->galaxy.stars.size();
		}
	}
}