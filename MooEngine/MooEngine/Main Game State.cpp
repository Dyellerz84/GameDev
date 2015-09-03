#include "Main Game State.h"

#include <random>

#include "Galaxy Creator.h"
#include "New Game Setup State.h"
#include "Galaxy View State.h"

MainGameState::MainGameState( MOO::MOOEngine* setEngine )
{
	engine = setEngine;

	gameData.galaxy = MOO::GameCreation::CreateStarSystems( engine, GalaxySize::Large );

	log.open("MainGameLog.txt");
	
	OutputGalaxyData();

	//DeterminePlayerHome();
	
	stateStack.push( new GalaxyViewState( setEngine, &gameData ));

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
		/*case MainGameStates::Research:
		{
			stateStack.top()->nextState = MainGameStates::NoChange;

			stateStack.push( new ResearchState ( engine ) );

			break;
		}*/
				
		case MainGameStates::Quit:
		{
			delete stateStack.top();

			stateStack.pop();
			
			break;
		}

		case MainGameStates::TurnUpdate:
		{
			stateStack.top()->nextState = MainGameStates::NoChange;
			RunTurnUpdates();

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

			output << std::endl;
		}
	}
}

/*void MainGameState::DeterminePlayerHome()
{
	std::random_device seeder;

	std::default_random_engine random( seeder );

	std::uniform_int_distribution<unsigned int> uniformDistributor(0, gameData.galaxy.stars.size() );

	std::unordered_set<unsigned int> attemptedStars;

	unsigned int starNumber;

	bool homeSet = false;
	
	while( homeSet == false )
	{
		log << "Determining Home System..." << std::endl;

		do
		{
			starNumber = uniformDistributor( random );
		}
		while( attemptedStars.find( starNumber ) != attemptedStars.end() );

		for(unsigned int i = 0; i < gameData.galaxy.stars[starNumber].planets.size(); i++)
		{
			if( gameData.galaxy.stars[starNumber].planets[i].climate == ClimateType::Terran && gameData.galaxy.stars[starNumber].planets[i].mineralQuality == MineralQuality::Abundant )
			{
				homeSet = true;
				i = gameData.galaxy.stars[starNumber].planets.size();
			}
		}

		attemptedStars.insert( starNumber );

		if(attemptedStars.size() == gameData.galaxy.stars.size())
		{
			homeSet = true;

			starNumber = uniformDistributor(random);

			gameData.galaxy.stars[starNumber].name = "Home System";

			gameData.galaxy.stars[starNumber].planets.clear();

			std::unordered_set< unsigned short int > usedOrbits;
			std::uniform_int_distribution<unsigned short int> numberOfPlanetsGenerator(0,8);
			std::uniform_int_distribution<unsigned int> planetSize(0,4);
			std::uniform_int_distribution<unsigned short int> degreesPerTurn(1,10);
			std::uniform_int_distribution<unsigned short int> startingOrbitDegree(0, 355);
			std::uniform_int_distribution<unsigned int> d7( 0,6 );

			usedOrbits.insert( 4 );

			PlanetData newPlanet;

			newPlanet.name = "Home World";
			newPlanet.climate = ClimateType::Terran;
			newPlanet.mineralQuality = MineralQuality::Abundant;
			newPlanet.size = PlanetSize::Medium;
			newPlanet.baseMaximumPopulation = (newPlanet.climate + 1) * (newPlanet.size + 1);
			newPlanet.solarLocation = 4;

			newPlanet.degreesPerTurn = degreesPerTurn( random );
			newPlanet.currentOrbitDegree = startingOrbitDegree( random );

			gameData.galaxy.stars[starNumber].planets.push_back( newPlanet );
			
			unsigned int numberOfPlanets = numberOfPlanetsGenerator( random );

			for(unsigned int i = 0; i < numberOfPlanets; i++)
			{
				unsigned short int orbitLocation;

				do
				{
					orbitLocation = numberOfPlanetsGenerator( random );
				}
				while( usedOrbits.find( orbitLocation ) != usedOrbits.end() );

				usedOrbits.insert( orbitLocation );

				newPlanet.solarLocation = orbitLocation;
					
				newPlanet.degreesPerTurn = degreesPerTurn( random );
				
				newPlanet.currentOrbitDegree = startingOrbitDegree( random );

					switch( planetSize( random ) )
					{
						case 0:
						{
							newPlanet.size = PlanetSize::Tiny;

							break;
						}

						case 1:
						{
							newPlanet.size = PlanetSize::Small;

							break;
						}

						case 2:
						{
							newPlanet.size = PlanetSize::Medium;

							break;
						}

						case 3:
						{
							newPlanet.size = PlanetSize::Large;

							break;
						}

						case 4:
						{
							newPlanet.size = PlanetSize::Huge;

							break;
						}
					}

					switch( planetSize( random ) )
					{
						case 0:
						{
							newPlanet.mineralQuality = MineralQuality::UltraPoor;

							break;
						}

						case 1:
						{
							newPlanet.mineralQuality = MineralQuality::Poor;

							break;
						}

						case 2:
						{
							newPlanet.mineralQuality = MineralQuality::Abundant;

							break;
						}

						case 3:
						{
							newPlanet.mineralQuality = MineralQuality::Rich;

							break;
						}

						case 4:
						{
							newPlanet.mineralQuality = MineralQuality::UltraRich;

							break;
						}
					}

					switch( d7( random ) )
					{
						case 0:
						{
							newPlanet.climate = ClimateType::Toxic;

							break;
						}

						case 1:
						{
							newPlanet.climate = ClimateType::Radiated;

							break;
						}

						case 2:
						{
							newPlanet.climate = ClimateType::Barren;

							break;
						}

						case 3:
						{
							if( newPlanet.solarLocation <= 4 )
							{
								newPlanet.climate = ClimateType::Desert;
							}

							else
							{
								newPlanet.climate = ClimateType::Tundra;
							}
						
							break;
						}

						case 4:
						{
							if( newPlanet.solarLocation <= 4 )
							{
								newPlanet.climate = ClimateType::Swamp;
							}

							else
							{
								newPlanet.climate = ClimateType::Ocean;
							}

							break;
						}

						case 5:
						{
							
							newPlanet.climate = ClimateType::Terran;
							
							break;
						}

						case 6:
						{
							newPlanet.climate = ClimateType::Paradise;

							break;
						}
					}

					newPlanet.baseMaximumPopulation = (newPlanet.size + 1) * (newPlanet.climate + 1);

					newPlanet.name = gameData.galaxy.stars[starNumber].name + " " + MOO::Globals::GetRomanNumeralFromNumber( newPlanet.solarLocation );

					gameData.galaxy.stars[starNumber].planets.push_back( newPlanet );
			}
		}
	}

	gameData.galaxy.stars[starNumber].name = "Home";

	for(unsigned int i = 0; i < gameData.galaxy.stars[starNumber].planets.size(); i++)
	{
		gameData.galaxy.stars[starNumber].planets[i].name = gameData.galaxy.stars[starNumber].name + " " + MOO::Globals::GetRomanNumeralFromNumber( gameData.galaxy.stars[starNumber].planets[i].solarLocation );
	}

	for(unsigned int i = 0; i < gameData.galaxy.stars.size(); i++)
	{
		if( i != starNumber )
		{
			std::stringstream starName;

			starName << gameData.galaxy.stars[i].GetStarTypeString();

			unsigned int xDistanceFromHome =  gameData.galaxy.stars[i].location.x - gameData.galaxy.stars[starNumber].location.x;
			unsigned int yDistanceFromHome =  gameData.galaxy.stars[i].location.y - gameData.galaxy.stars[starNumber].location.y;

			unsigned int distanceFromHome = std::sqrt( float(xDistanceFromHome * xDistanceFromHome) + float(yDistanceFromHome * yDistanceFromHome) );
	
			starName << "-" << distanceFromHome;

			gameData.galaxy.stars[i].name = starName.str();

			for(unsigned int j = 0; j < gameData.galaxy.stars[i].planets.size(); j++)
			{
				std::stringstream planetName;

				planetName <<  gameData.galaxy.stars[i].name << " " << MOO::Globals::GetRomanNumeralFromNumber(gameData.galaxy.stars[i].planets[j].solarLocation);

				gameData.galaxy.stars[i].planets[j].name = planetName.str();
			}
		}
	}

	log << "starNumber = " << starNumber << std::endl;

	gameData.empires[0].homeSystem = starNumber;

	SetupStartingColonies();
	SetupStartingFleet();
}*/

/*void MainGameState::SetupStartingColonies()
{
	log << "Setting Up Starting Colonies..." << std::endl;

	for(unsigned int i = 0; i < gameData.empires.size(); i++)
	{
		bool planetFound = false;

		while( planetFound == false )
		{
			for(unsigned int j = 0; j < gameData.galaxy.stars[gameData.empires[i].homeSystem].planets.size(); j++)
			{
				log << "Searching for planet" << std::endl;

				if( gameData.galaxy.stars[gameData.empires[i].homeSystem].planets[j].climate == ClimateType::Terran && gameData.galaxy.stars[gameData.empires[i].homeSystem].planets[j].mineralQuality == MineralQuality::Abundant)
				{
					planetFound = true;

					gameData.galaxy.stars[gameData.empires[i].homeSystem].planets[j].colonyData = new ColonyData;

					gameData.empires[i].colonies.push_back( gameData.galaxy.stars[gameData.empires[i].homeSystem].planets[j].colonyData );

					gameData.galaxy.stars[gameData.empires[i].homeSystem].planets[j].colonyData->name = "Home World";

					unsigned long int startingPopulation = gameData.galaxy.stars[gameData.empires[i].homeSystem].planets[j].baseMaximumPopulation / 4;

					startingPopulation *= 3;

					gameData.galaxy.stars[gameData.empires[i].homeSystem].planets[j].colonyData->population.push_back( PopulationData( startingPopulation ) );

					j = gameData.galaxy.stars[gameData.empires[i].homeSystem].planets.size();
				}
			}
		}
	}

	log << "Starting Colonies Setup!" << std::endl;
}*/

/*void MainGameState::SetupStartingFleet()
{
	ShipData newShip;

	newShip.warpSpeed = 1;

	FleetData newFleet;

	newFleet.ships.push_back(newShip);
	newFleet.warpSpeed = 2;

	newFleet.location = gameData.galaxy.stars[gameData.empires[0].homeSystem].location;

	gameData.empires[0].fleets.push_back( newFleet );
}*/

void MainGameState::RunTurnUpdates()
{
	UpdateStarSystems();
}

void MainGameState::UpdateStarSystems()
{
	for(unsigned int i = 0; i < gameData.galaxy.stars.size(); i++)
	{
		for(unsigned int j = 0; j < gameData.galaxy.stars[i].planets.size(); j++)
		{
			gameData.galaxy.stars[i].planets[j].currentOrbitDegree += gameData.galaxy.stars[i].planets[j].degreesPerTurn;
		}
	}
}

/*void UpdateFleets( std::vector<FleetData>* fleets )
{
	for(unsigned int i = 0; i < fleets->size(); i++)
	{
		if( (*fleets)[i].location != (*fleets)[i].destination )
		{
			float xDistance = (*fleets)[i].destination.x - (*fleets)[i].location.x;
			float yDistance = (*fleets)[i].destination.y - (*fleets)[i].location.y;

			float degrees = std::atan2( yDistance, xDistance ) * MOO::Globals::RadiansToDegrees;

			(*fleets)[i].location.x = std::cos( degrees ) * (*fleets)[i].warpSpeed * MOO::Globals::RadiansToDegrees;
			(*fleets)[i].location.y = std::sin( degrees ) * (*fleets)[i].warpSpeed * MOO::Globals::RadiansToDegrees;
		}
	}
}*/

/*void MainGameState::UpdateEmpires()
{
	for(unsigned int i = 0; i < gameData.empires.size(); i++)
	{
		UpdateFleets( &gameData.empires[i].fleets );
	}
}*/