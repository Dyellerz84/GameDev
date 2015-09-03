#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace MOO
{
	namespace Globals
	{
		inline bool CheckIfInsideShape( sf::Rect<unsigned short int>& shape, const sf::Vector2f& point)
		{
			return shape.contains( point.x, point.y );
		}

		inline std::string GetRomanNumeralFromNumber( unsigned int number )
		{
			switch( number )
			{
			case 1:

				return "I";
				break;

			case 2: 
				
				return "II";
				break;

			case 3: 

				return "III";
				break;

			case 4: 

				return "IV";
				break;

			case 5:

				return "V";
				break;

			case 6: 

				return "VI";
				break;

			case 7:

				return "VII";
				break;

			case 8: 

				return "VIII";
				break;

			case 9: 
				
				return "IX";
				break;

			default:

				return "Number too big - function still WIP";
				break;
			}
		}
	}
}
