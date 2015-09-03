#pragma once

#include <SFML/Graphics.hpp>

namespace MOO
{
	namespace Globals
	{
		inline bool CheckIfInsideShape( sf::Rect<unsigned short int>& shape, const sf::Vector2f& point)
		{
			return shape.contains( point.x, point.y );
		}
	}
}
