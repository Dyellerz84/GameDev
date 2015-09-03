#include "System View State.h"

#include <cmath>

SystemViewState::SystemViewState(MOO::MOOEngine* setEngine, StarData* setSystem) : GameStateBase( setEngine, MainGameStates::NoChange )
{
	starSystem = setSystem;

	gameFont.loadFromFile("cour.ttf");

	LoadImages();
}

SystemViewState::~SystemViewState()
{

}

void SystemViewState::HandleInput()
{
	while( engine->GetUserInput( userInput ) )
	{
		if( userInput.type == sf::Event::KeyPressed )
		{
			if( userInput.key.code == sf::Keyboard::Q )
			{
				for(unsigned int i = 0; i < starSystem->planets.size(); i++)
				{
					starSystem->planets[i].currentOrbitDegree += starSystem->planets[i].degreesPerTurn;
				}
			}
		}

		if(userInput.type == sf::Event::KeyReleased)
		{
			if(userInput.key.code == sf::Keyboard::Escape)
			{
				nextState = MainGameStates::Quit;
			}
		}
	}
}

void SystemViewState::HandleLogic()
{
	bool shouldDisplay = false;

	for(unsigned int i = 0; i < starSystem->planets.size(); i++)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition();
		
		unsigned int orbitWidth = 40;

		unsigned int orbitDistance = (starSystem->planets[i].solarLocation + 1) * orbitWidth;
			
		int x = orbitDistance * std::cos( starSystem->planets[i].currentOrbitDegree * MOO::Globals::DegreesToRadians ) + (MOO::Globals::gameWidth / 2);
		int y = orbitDistance * std::sin( starSystem->planets[i].currentOrbitDegree * MOO::Globals::DegreesToRadians ) + (MOO::Globals::gameHeight / 2); 

		int xDistance = mousePosition.x - x;
		int yDistance = mousePosition.y - y;

		if( xDistance * xDistance + yDistance * yDistance <= (images.aridPlanetImage.getGlobalBounds().width / 2) * (images.aridPlanetImage.getGlobalBounds().width / 2) )
		{
			shouldDisplay = true;
			planetDataToDisplay = i;

			i = starSystem->planets.size();
		}

		else
		{
			shouldDisplay = false;
		}
	}

	displayPlanetData = shouldDisplay;
}

void SystemViewState::HandleOutput()
{
		unsigned int X = (MOO::Globals::gameWidth / 2);
		unsigned int Y = (MOO::Globals::gameHeight / 2);

		sf::Text nameDisplay;

		nameDisplay.setFont( gameFont );

		switch( starSystem->starType )
		{
			case StarType::O:
			{
				images.OStarImage.setPosition( X, Y );

				engine->Draw( images.OStarImage );

				break;
			}

			case StarType::A:
			{
				images.AStarImage.setPosition( X, Y );

				engine->Draw( images.AStarImage );

				break;
			}

			case StarType::B:
			{
				images.BStarImage.setPosition( X, Y );

				engine->Draw( images.BStarImage );

				break;
			}

			case StarType::F:
			{
				images.FStarImage.setPosition( X, Y );

				engine->Draw( images.FStarImage );

				break;
			}

			case StarType::G:
			{
				images.GStarImage.setPosition( X, Y );

				engine->Draw( images.GStarImage );

				break;
			}

			case StarType::K:
			{
				images.KStarImage.setPosition( X, Y );

				engine->Draw( images.KStarImage );

				break;
			}

			case StarType::M:
			{
				images.MStarImage.setPosition( X, Y );

				engine->Draw( images.MStarImage );

				break;
			}
	}
		nameDisplay.setString( starSystem->name );
		nameDisplay.setCharacterSize(72);
		nameDisplay.setPosition( 0, 0 );

		engine->Draw(nameDisplay);

		for(unsigned int i = 0; i < starSystem->planets.size(); i++)
		{
			unsigned int orbitWidth = 40;

			unsigned int orbitDistance = (starSystem->planets[i].solarLocation + 1) * orbitWidth;
			
			int x = orbitDistance * std::cos( starSystem->planets[i].currentOrbitDegree * MOO::Globals::DegreesToRadians ) + (MOO::Globals::gameWidth / 2);
			int y = orbitDistance * std::sin( starSystem->planets[i].currentOrbitDegree * MOO::Globals::DegreesToRadians ) + (MOO::Globals::gameHeight / 2); 

			float sizeScale = 1;

			sf::CircleShape orbitCircle( orbitDistance, 120 );

			orbitCircle.setFillColor( sf::Color( 0, 0, 0, 0) );
			orbitCircle.setOutlineThickness( 2 );
			orbitCircle.setOutlineColor( sf::Color(	50, 50, 50) );
			orbitCircle.setOrigin( orbitDistance , orbitDistance );
			orbitCircle.setPosition( X, Y);

			engine->Draw( orbitCircle );

			switch( starSystem->planets[i].size )
			{
				case PlanetSize::Tiny:
					{
						sizeScale = 0.5;

						break;
					}

				case PlanetSize::Small:
					{
						sizeScale = 0.75;

						break;
					}

				case PlanetSize::Large:
					{
						sizeScale = 1.25;

						break;
					}

				case PlanetSize::Huge:
					{
						sizeScale = 1.5;

						break;
					}
			}

			switch( starSystem->planets[i].climate )
			{
				case ClimateType::Arid:
					{
						sf::Sprite planet(images.aridPlanetImage);

						planet.setScale( sizeScale, sizeScale );
						
						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}

				case ClimateType::Barren:
					{
						sf::Sprite planet(images.barrenPlanetImage);

						planet.setScale( sizeScale, sizeScale );

						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}

				case ClimateType::Desert:
					{
						sf::Sprite planet(images.desertPlanetImage);

						planet.setScale( sizeScale, sizeScale );

						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}

				case ClimateType::Ocean:
					{
						sf::Sprite planet(images.desertPlanetImage);

						planet.setScale( sizeScale, sizeScale );

						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}

				case ClimateType::Paradise:
					{
						sf::Sprite planet(images.paradisePlanetImage);

						planet.setScale( sizeScale, sizeScale );

						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}

				case ClimateType::Radiated:
					{
						sf::Sprite planet(images.radiatedPlanetImage);

						planet.setScale( sizeScale, sizeScale );

						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}

				case ClimateType::Swamp:
					{
						sf::Sprite planet(images.swampPlanetImage);

						planet.setScale( sizeScale, sizeScale );

						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}

				case ClimateType::Terran:
					{
						sf::Sprite planet(images.desertPlanetImage);

						planet.setScale( sizeScale, sizeScale );

						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}

				case ClimateType::Toxic:
					{
						sf::Sprite planet(images.toxicPlanetImage);

						planet.setScale( sizeScale, sizeScale );

						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}

				case ClimateType::Tundra:
					{
						sf::Sprite planet(images.tundraPlanetImage);

						planet.setScale( sizeScale, sizeScale );

						planet.setPosition( x, y );

						engine->Draw( planet );

						break;
					}
			}

		}

		if( displayPlanetData )
		{
			unsigned int orbitWidth = 40;

			unsigned int orbitDistance = (starSystem->planets[planetDataToDisplay].solarLocation + 1) * orbitWidth;
			
			int x = orbitDistance * std::cos( starSystem->planets[planetDataToDisplay].currentOrbitDegree * MOO::Globals::DegreesToRadians ) + (MOO::Globals::gameWidth / 2);
			int y = orbitDistance * std::sin( starSystem->planets[planetDataToDisplay].currentOrbitDegree * MOO::Globals::DegreesToRadians ) + (MOO::Globals::gameHeight / 2); 
			
			y += 30;

			sf::Text displaytext;

			displaytext.setFont( gameFont );
			displaytext.setPosition( x, y );
			displaytext.setString( starSystem->planets[planetDataToDisplay].name );
							
			engine->Draw( displaytext );

			displaytext.setString( starSystem->planets[planetDataToDisplay].GetSizeString() );
			displaytext.setPosition( x, displaytext.getPosition().y + displaytext.getGlobalBounds().height );

			engine->Draw( displaytext );

			displaytext.setString( starSystem->planets[planetDataToDisplay].GetClimateString() );
			displaytext.setPosition( x, displaytext.getPosition().y + displaytext.getGlobalBounds().height );

			engine->Draw( displaytext );
			
			displaytext.setString( starSystem->planets[planetDataToDisplay].GetMineralString() );
			displaytext.setPosition( x, displaytext.getPosition().y + displaytext.getGlobalBounds().height );

			engine->Draw( displaytext );
		}
}

void SystemViewState::LoadImages()
{
	images.OStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/O Star.png" );
	images.OStarImage.setOrigin( images.OStarImage.getGlobalBounds().width / 2, images.OStarImage.getGlobalBounds().height / 2);
		
	images.BStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/B Star.png" );
	images.BStarImage.setOrigin( images.BStarImage.getGlobalBounds().width / 2, images.BStarImage.getGlobalBounds().height / 2);

	images.AStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/A Star.png" );
	images.AStarImage.setOrigin( images.AStarImage.getGlobalBounds().width / 2, images.AStarImage.getGlobalBounds().height / 2);

	images.FStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/F Star.png" );
	images.FStarImage.setOrigin( images.FStarImage.getGlobalBounds().width / 2, images.FStarImage.getGlobalBounds().height / 2);

	images.GStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/G Star.png" );
	images.GStarImage.setOrigin( images.GStarImage.getGlobalBounds().width / 2, images.GStarImage.getGlobalBounds().height / 2);

	images.KStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/K Star.png" );
	images.KStarImage.setOrigin( images.KStarImage.getGlobalBounds().width / 2, images.KStarImage.getGlobalBounds().height / 2);

	images.MStarImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/M Star.png" );
	images.MStarImage.setOrigin( images.MStarImage.getGlobalBounds().width / 2, images.MStarImage.getGlobalBounds().height / 2);

	images.aridPlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Arid Planet.png" );
	images.aridPlanetImage.setOrigin( images.aridPlanetImage.getGlobalBounds().width / 2, images.aridPlanetImage.getGlobalBounds().height / 2);

	images.barrenPlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Barren Planet.png" );
	images.barrenPlanetImage.setOrigin( images.barrenPlanetImage.getGlobalBounds().width / 2, images.barrenPlanetImage.getGlobalBounds().height / 2);

	images.desertPlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Desert Planet.png" );
	images.desertPlanetImage.setOrigin( images.desertPlanetImage.getGlobalBounds().width / 2, images.desertPlanetImage.getGlobalBounds().height / 2);

	images.oceanPlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Ocean Planet.png" );
	images.oceanPlanetImage.setOrigin( images.oceanPlanetImage.getGlobalBounds().width / 2, images.oceanPlanetImage.getGlobalBounds().height / 2);

	images.paradisePlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Paradise Planet.png" );
	images.paradisePlanetImage.setOrigin( images.paradisePlanetImage.getGlobalBounds().width / 2, images.paradisePlanetImage.getGlobalBounds().height / 2);

	images.radiatedPlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Radiated Planet.png" );
	images.radiatedPlanetImage.setOrigin( images.radiatedPlanetImage.getGlobalBounds().width / 2, images.radiatedPlanetImage.getGlobalBounds().height / 2);

	images.swampPlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Swamp Planet.png" );
	images.swampPlanetImage.setOrigin( images.swampPlanetImage.getGlobalBounds().width / 2, images.swampPlanetImage.getGlobalBounds().height / 2);

	images.terranPlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Terran Planet.png" );
	images.terranPlanetImage.setOrigin( images.terranPlanetImage.getGlobalBounds().width / 2, images.terranPlanetImage.getGlobalBounds().height / 2);

	images.toxicPlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Toxic Planet.png" );
	images.toxicPlanetImage.setOrigin( images.toxicPlanetImage.getGlobalBounds().width / 2, images.toxicPlanetImage.getGlobalBounds().height / 2);

	images.tundraPlanetImage = engine->imageManager.LoadNewImage( "Resources/Main Game State/Galaxy View/Tundra Planet.png" );
	images.tundraPlanetImage.setOrigin( images.tundraPlanetImage.getGlobalBounds().width / 2, images.tundraPlanetImage.getGlobalBounds().height / 2);

}