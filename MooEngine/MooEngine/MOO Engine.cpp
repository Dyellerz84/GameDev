#include "MOO Engine.h"

#include "Global Constants.h"

MOO::MOOEngine::MOOEngine()
{
	gameVersion = "MOO Clone Alpha Build - 0";
	
	if( systemSettings.screenWidth == 0)
	{
		app.create( sf::VideoMode::getDesktopMode(), gameVersion, sf::Style::Fullscreen );

		app.setView(camera);

		systemSettings.screenHeight = app.getSize().y;
		systemSettings.screenWidth = app.getSize().x;

		camera.setSize(systemSettings.screenWidth, systemSettings.screenWidth);

		systemSettings.SaveSettings();
	}

	else
	{
		app.create( sf::VideoMode( systemSettings.screenWidth, systemSettings.screenHeight ), gameVersion, sf::Style::Fullscreen );
	}

	screenScaleX = float( app.getSize().x ) / float ( MOO::Globals::gameWidth );
	screenScaleY = float( app.getSize().y ) / float ( MOO::Globals::gameHeight );

	app.setFramerateLimit(60);

	zoomFactor = 1.0f;

	useZoom = false;
	
	gameToLaunch.clear();
}

MOO::MOOEngine::~MOOEngine()
{

}

sf::Vector2f MOO::MOOEngine::GetMousePostion()
{
	return sf::Vector2f( sf::Mouse::getPosition().x / screenScaleX, sf::Mouse::getPosition().y / screenScaleY);
}

void MOO::MOOEngine::Draw(sf::Sprite &spriteToDraw)
{
	if( useZoom == false )
	{
		spriteToDraw.setScale( screenScaleX, screenScaleY );

		spriteToDraw.setPosition( spriteToDraw.getPosition().x * screenScaleX, spriteToDraw.getPosition().y * screenScaleY );

		app.draw( spriteToDraw );

		spriteToDraw.setPosition( spriteToDraw.getPosition().x / screenScaleX, spriteToDraw.getPosition().y / screenScaleY );
	}

	else
	{
		spriteToDraw.setScale( screenScaleX * zoomFactor, screenScaleY * zoomFactor );

		spriteToDraw.setPosition( spriteToDraw.getPosition().x * screenScaleX * zoomFactor, spriteToDraw.getPosition().y * screenScaleY * zoomFactor);

		app.draw( spriteToDraw );

		spriteToDraw.setPosition( spriteToDraw.getPosition().x / screenScaleX / zoomFactor, spriteToDraw.getPosition().y / screenScaleY / zoomFactor);
	}
}

bool MOO::MOOEngine::GetUserInput( sf::Event &getInput)
{
	if( app.pollEvent( getInput ) )
	{
		return true;
	}

	else
	{
		return false;
	}
}

void MOO::MOOEngine::ClearScreen()
{
	app.clear();
}

void MOO::MOOEngine::DisplayScreen()
{
	app.display();
}

void MOO::MOOEngine::ResetAllManagers()
{
	imageManager.Reset();
	soundManager.Reset();
	musicManager.Reset();
}

void MOO::MOOEngine::Draw(sf::RectangleShape &rectangleToDraw)
{
	rectangleToDraw.setScale( screenScaleX, screenScaleY );

	rectangleToDraw.setPosition( rectangleToDraw.getPosition().x * screenScaleX, rectangleToDraw.getPosition().y * screenScaleY );

	app.draw( rectangleToDraw );

	rectangleToDraw.setPosition( rectangleToDraw.getPosition().x / screenScaleX, rectangleToDraw.getPosition().y / screenScaleY );
}

void MOO::MOOEngine::Draw(sf::Text &textToDraw)
{
	textToDraw.setScale( screenScaleX, screenScaleY );

	textToDraw.setPosition( textToDraw.getPosition().x * screenScaleX, textToDraw.getPosition().y * screenScaleY );

	app.draw( textToDraw );

	textToDraw.setPosition( textToDraw.getPosition().x / screenScaleX, textToDraw.getPosition().y / screenScaleY );
}

std::vector<sf::VideoMode> MOO::MOOEngine::GetAllVideoModes()
{
	return sf::VideoMode::getFullscreenModes();
}

MOO::SystemSettings* MOO::MOOEngine::GetSystemSettings()
{
	return &systemSettings;
}

void MOO::MOOEngine::Draw( sf::CircleShape &circleToDraw )
{
	circleToDraw.setScale( screenScaleX, screenScaleY );

	circleToDraw.setPosition( circleToDraw.getPosition().x * screenScaleX, circleToDraw.getPosition().y * screenScaleY );

	app.draw( circleToDraw );
}

void MOO::MOOEngine::SetZoomFactor( float setZoomFactor )
{
	zoomFactor = setZoomFactor;
}

void MOO::MOOEngine::TurnZoomOn()
{
	useZoom = true;
}

void MOO::MOOEngine::TurnZoomOff()
{
	useZoom = false;
}
