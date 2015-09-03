#pragma once

#include <vector>
#include <unordered_set>
#include <queue>

#include <SFML/Graphics.hpp>

#include "Colony Data.h"

struct BuildProject
{
	std::string name;
	unsigned int costRemaining;
};

namespace ClimateType
{
	enum Type { Toxic, Radiated, Barren, Desert, Arid, Tundra, Swamp, Ocean, Terran, Paradise };
}

namespace MineralQuality
{
	enum Type { UltraPoor, Poor, Abundant, Rich, UltraRich };
}

namespace PlanetSize
{
	enum Type { Tiny, Small, Medium, Large, Huge };
}

struct PlanetData
{
	unsigned short int solarLocation;
		
	unsigned short int baseMaximumPopulation;

	sf::Sprite planetImage;

	ClimateType::Type climate;

	MineralQuality::Type mineralQuality;

	PlanetSize::Type size; 

	ColonyData* colonyData;

	std::string name;

	unsigned short int degreesPerTurn;
	unsigned short int currentOrbitDegree;

	PlanetData();

	std::string GetClimateString();
	std::string GetSizeString();
	std::string GetMineralString();
};

inline PlanetData::PlanetData()
{
	colonyData = NULL;
}

inline std::string PlanetData::GetClimateString()
{
	switch( climate )
	{
		case ClimateType::Arid:
			{
				return std::string("Arid");

				break;
			}

		case ClimateType::Barren:
			{
				return std::string("Barren");

				break;
			}

		case ClimateType::Desert:
			{
				return std::string("Desert");

				break;
			}

		case ClimateType::Ocean:
			{
				return std::string("Ocean");

				break;
			}

		case ClimateType::Paradise:
			{
				return std::string("Paradise");

				break;
			}

		case ClimateType::Radiated:
			{
				return std::string("RAdiated");

				break;
			}

		case ClimateType::Swamp:
			{
				return std::string("Swamp");

				break;
			}

		case ClimateType::Terran:
			{
				return std::string("Terran");

				break;
			}

		case ClimateType::Toxic:
			{
				return std::string("Toxic");

				break;
			}

		case ClimateType::Tundra:
			{
				return std::string("Tundra");

				break;
			}

		default:

			return "Error";

			break;
	}
}

inline std::string PlanetData::GetSizeString()
{
	switch( size )
	{
		case PlanetSize::Tiny:
			{
				return std::string("Tiny");

				break;
			}

		case PlanetSize::Small:
			{
				return std::string("Small");

				break;
			}

		case PlanetSize::Medium:
			{
				return std::string("Medium");

				break;
			}

		case PlanetSize::Large:
			{
				return std::string("Large");

				break;
			}

		case PlanetSize::Huge:
			{
				return std::string("Huge");

				break;
			}
	}
}

inline std::string PlanetData::GetMineralString()
{
	switch( mineralQuality )
	{
		case MineralQuality::UltraPoor:
			{
				return std::string("Ultra Poor");

				break;
			}

		case MineralQuality::Poor:
			{
				return std::string("Poor");

				break;
			}

		case MineralQuality::Abundant:
			{
				return std::string("Abundant");

				break;
			}

		case MineralQuality::Rich:
			{
				return std::string("Rich");

				break;
			}

		case MineralQuality::UltraRich:
			{
				return std::string("Ultra Rich");

				break;
			}

		default:

			return std::string("Error");

			break;
	}
}
