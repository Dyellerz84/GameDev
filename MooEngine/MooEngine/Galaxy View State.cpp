#include "Galaxy View State.h"
#include <sstream>

GalaxyViewState::GalaxyViewState(MOO::MOOEngine* setEngine, Game::GameData* setGameData) : GameStateBase( setEngine, MainGameStates::NoChange )
{
	gameData = setGameData;
	gameEngine = setEngine;

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
	
	//PutCameraOnHome();
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

		log << temp.size();

		for(unsigned int i = 0; i < temp.size(); i++)
		{
			engine->Draw( temp[i] );
		}
	
		log << " Sprites Drawn" << std::endl;
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
	sf::Sprite buttonImage;// = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/ResearchButton.png" );
	sf::Sound buttonSound = engine->soundManager.LoadNewSound("Resources/Title State/ButtonSound.wav");

	//ui.AddButton(new MOO::UI::Buttons::EventButton<GalaxyViewStateEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, buttonImage, buttonSound, GalaxyViewStateEvents::GotoResearch, sf::Vector2f( 1430, 800 ) ) );

	//advance turn button

	buttonShape.top = 900;
	buttonImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/TurnButton.png");

	ui.AddButton(new MOO::UI::Buttons::EventButton<GalaxyViewStateEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, buttonImage, buttonSound, GalaxyViewStateEvents::TurnUpdate, sf::Vector2f( 1430, 900 ) ) );
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

			case GalaxyViewStateEvents::TurnUpdate:
			{
				nextState = MainGameStates::TurnUpdate;

				break;
			}
		}
	}
}

void GalaxyViewState::DrawStars()
{
	engine->camera.zoom(zoomFactor);

	for (unsigned int i = 0; i < gameData->galaxy.stars.size(); i++)
	{
		float starX = gameData->galaxy.stars[i].location.x;
		float starY = gameData->galaxy.stars[i].location.y;

		switch (gameData->galaxy.stars[i].starType)
		{
		case StarType::O:
		{
			galaxyImages.OStarImage.setPosition(starX, starY);

			engine->Draw(galaxyImages.OStarImage);

			break;
		}

		case StarType::A:
		{
			galaxyImages.AStarImage.setPosition(starX, starY);

			engine->Draw(galaxyImages.AStarImage);

			break;
		}

		case StarType::B:
		{
			galaxyImages.BStarImage.setPosition(starX, starY);

			engine->Draw(galaxyImages.BStarImage);

			break;
		}

		case StarType::F:
		{
			galaxyImages.FStarImage.setPosition(starX, starY);

			engine->Draw(galaxyImages.FStarImage);

			break;
		}

		case StarType::G:
		{
			galaxyImages.GStarImage.setPosition(starX, starY);

			engine->Draw(galaxyImages.GStarImage);

			break;
		}

		case StarType::K:
		{
			galaxyImages.KStarImage.setPosition(starX, starY);

			engine->Draw(galaxyImages.KStarImage);

			break;
		}

		case StarType::M:
		{
			galaxyImages.MStarImage.setPosition(starX, starY);

			engine->Draw(galaxyImages.MStarImage);

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
			engine->camera.move(previousMousex - currentMouseX, 0);
			
			previousMousex = currentMouseX;
		}
		
		if( previousMousey != currentMouseY )
		{
			engine->camera.move(0, previousMousey - currentMouseY);

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

		case sf::Keyboard::Space:
		{
			//PutCameraOnHome();
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
	zoomFactor += userInput.mouseWheel.delta * 0.1;	
	
	if (zoomFactor < 0.01)
		zoomFactor = 0.1;
	else if (zoomFactor > 1.00)
		zoomFactor = 1.00;

	engine->camera.zoom(zoomFactor);
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
	for(unsigned int i = 0; i < gameData->galaxy.stars.size(); i++)
	{
		if( CheckMouseClick( mousePosition, gameData->galaxy.stars[i].location, 25 ) )
		{
			systemBeingViewed = &gameData->galaxy.stars[i];

			i = gameData->galaxy.stars.size();
		}
	}
}

bool GalaxyViewState::CheckMouseClick( sf::Vector2f mousePosition, sf::Vector2f testLocation, int radius)
{
	unsigned int screenXCenter = (MOO::Globals::gameWidth / 2);
	unsigned int screenYCenter = (MOO::Globals::gameHeight / 2);

	unsigned int galaxyXCenter = gameData->galaxy.radius / 2;
	unsigned int galaxyYCenter = gameData->galaxy.radius / 2;
		
	unsigned int centeringAdjustmentX = screenXCenter / zoomFactor - galaxyXCenter;
	unsigned int centeringAdjustmentY = screenYCenter / zoomFactor - galaxyYCenter;

	unsigned int xDistance = mousePosition.x - ((centeringAdjustmentX + testLocation.x) - xCamera) * zoomFactor;
	unsigned int yDistance = mousePosition.y - ((centeringAdjustmentY + testLocation.y) - yCamera) * zoomFactor;

	if( xDistance * xDistance + yDistance * yDistance <= ( 625 * zoomFactor ) )
	{
		return true;
	}

	else 
	{
		return false;
	}
}

/*void GalaxyViewState::PutCameraOnHome()
{
	log << "Home system is star " << gameData->empires[0].homeSystem << std::endl;

	xCamera = gameData->galaxy.stars[gameData->empires[0].homeSystem].location.x - gameData->galaxy.radius / 2;
	yCamera = gameData->galaxy.stars[gameData->empires[0].homeSystem].location.y - gameData->galaxy.radius / 2;
}*/

/*void GalaxyViewState::CheckFleetClick( sf::Vector2f mousePosition )
{

	if( selectedFleet == NULL )
	{
		unsigned int radius = 25;

		for(unsigned int i = 0; i < gameData->empires[0].fleets.size(); i++)
		{
			if( !gameData->empires[0].fleets[i].inSystem )
			{
				if( CheckMouseClick( mousePosition, gameData->empires[0].fleets[i].location, radius ) )
				{
					selectedFleet = &gameData->empires[0].fleets[i];
				}
			}

			else
			{
				sf::Vector2f newLocation;

				newLocation.x = gameData->empires[0].fleets[i].location.x + 30;
				newLocation.y = gameData->empires[0].fleets[i].location.y - 30;

				if( CheckMouseClick( mousePosition, newLocation, radius ) )
				{
					selectedFleet = &gameData->empires[0].fleets[i];
				}
			}
		}
	}

	else
	{
		for(unsigned int i = 0; i < gameData->galaxy.stars.size(); i++)
		{
			if( CheckMouseClick( mousePosition, gameData->galaxy.stars[i].location, 25 ) )
			{
				selectedFleet->destination = gameData->galaxy.stars[i].location;
				i = gameData->galaxy.stars.size();
			}
		}

		selectedFleet = NULL;
	}
}*/