#pragma once

#include <SFML\Graphics.hpp>

#include <vector>

#include "Planet Data.h"

namespace StarType
{
	enum Type { O, B, A, F, G, K, M };
}

struct StarData
{
	sf::Vector2i location;
	StarType::Type starType;

	std::vector<PlanetData> planets;

	sf::Sprite starImage;

	std::string name;

	std::string GetStarTypeString();
};

inline std::string StarData::GetStarTypeString()
{
	switch( starType )
	{
	
		case StarType::A:
		{
			return std::string("A");
		}

		case StarType::O:
		{
			return std::string("O");
		}

		case StarType::B:
		{
			return std::string("B");
		}

		case StarType::F:
		{
			return std::string("F");
		}

		case StarType::G:
		{
			return std::string("G");
		}

		case StarType::K:
		{
			return std::string("K");
		}

		case StarType::M:
		{
			return std::string("M");
		}
	}
}
