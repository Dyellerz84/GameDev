#pragma once

#include <random>

#include "Galaxy Data.h"
#include "New Game Settings Data.h"

#include <cmath>
#include <sstream>


namespace MOO
{
	namespace GameCreation
	{
		StarType::Type DetermineStarType(unsigned int number)
		{
			if (number < 5)
			{
				return StarType::O;
			}

			if (number < 25)
			{
				return StarType::B;
			}

			if (number < 150)
			{
				return StarType::A;
			}

			if (number < 300)
			{
				return StarType::F;
			}

			if (number < 500)
			{
				return StarType::G;
			}

			if (number < 700)
			{
				return StarType::K;
			}

			return StarType::M;
		}

		GalaxyData CreateStarSystems(MOO::MOOEngine* engine, GalaxySize::Size galaxySize)
		{
			GalaxyData infantGalaxy;

			infantGalaxy.radius = 2000;

			std::random_device seeder;

			std::default_random_engine randomNumberGenerator(seeder());

			std::uniform_int_distribution<unsigned int> uniformDistributor_X(0, infantGalaxy.radius);

			std::uniform_int_distribution<unsigned int> uniformDistributor_Y(0, infantGalaxy.radius);

			std::uniform_int_distribution<unsigned short int> numberOfPlanetsGenerator(0, 8);

			std::uniform_int_distribution<unsigned int> planetSize(0, 4);

			std::uniform_int_distribution<unsigned int> d7(0, 6);

			std::uniform_int_distribution<unsigned int> D1000(0, 1000);

			std::uniform_int_distribution<unsigned short int> degreesPerTurn(1, 10);

			std::uniform_int_distribution<unsigned short int> startingOrbitDegree(0, 355);

			for (unsigned int i = 0; i < 200; i++)
			{
				StarData newStar;

				bool locationSet = false;

				while (locationSet == false && infantGalaxy.stars.size() > 0)
				{
					newStar.location.x = uniformDistributor_X(randomNumberGenerator);
					newStar.location.y = uniformDistributor_Y(randomNumberGenerator);

					for (unsigned int j = 0; j < infantGalaxy.stars.size(); j++)
					{
						int xDistance = infantGalaxy.stars[j].location.x - newStar.location.x;

						int yDistance = infantGalaxy.stars[j].location.y - newStar.location.y;

						if ((xDistance * xDistance) + (yDistance * yDistance) >= 1000)
						{
							locationSet = true;
						}

						else
						{
							locationSet = false;
							j = infantGalaxy.stars.size();
						}
					}
				}


				newStar.starType = DetermineStarType(D1000(randomNumberGenerator));

				if (i == 0)
				{
					newStar.name = "Home";
				}

				else
				{
					std::stringstream starName;

					starName << newStar.GetStarTypeString();

					unsigned int xDistanceFromHome = newStar.location.x - infantGalaxy.stars[0].location.x;
					unsigned int yDistanceFromHome = newStar.location.y - infantGalaxy.stars[0].location.y;

					unsigned int distanceFromHome = std::sqrt(float(xDistanceFromHome * xDistanceFromHome) + float(yDistanceFromHome * yDistanceFromHome));

					starName << "-" << distanceFromHome;

					newStar.name = starName.str();
				}

				unsigned short int numberOfPlanets = numberOfPlanetsGenerator(randomNumberGenerator);

				std::unordered_set<unsigned short int> orbitalPositionsUsed;

				for (unsigned int j = 0; j < numberOfPlanets; j++)
				{
					PlanetData newPlanet;

					unsigned int orbitalPosition;

					do
					{
						orbitalPosition = numberOfPlanetsGenerator(randomNumberGenerator);
					} while (orbitalPositionsUsed.find(orbitalPosition) != orbitalPositionsUsed.end());

					orbitalPositionsUsed.insert(orbitalPosition);

					newPlanet.solarLocation = orbitalPosition;

					std::stringstream planetName;

					planetName << newStar.name << newPlanet.solarLocation;

					newPlanet.name = planetName.str();

					newPlanet.degreesPerTurn = degreesPerTurn(randomNumberGenerator);

					newPlanet.currentOrbitDegree = startingOrbitDegree(randomNumberGenerator);

					switch (planetSize(randomNumberGenerator))
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

					switch (planetSize(randomNumberGenerator))
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

					switch (d7(randomNumberGenerator))
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
						if (newPlanet.solarLocation <= 4)
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
						if (newPlanet.solarLocation <= 4)
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

					newStar.planets.push_back(newPlanet);
				}

				infantGalaxy.stars.push_back(newStar);
			}

			return infantGalaxy;
		}
	}
}