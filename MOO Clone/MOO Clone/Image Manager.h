#pragma once

#include <unordered_map>
#include <string>

#include <SFML\Graphics.hpp>


namespace MOO
{
	namespace Visual
	{
		class ImageManager
		{
			
		private:

			std::unordered_map<std::string,sf::Texture> images;

		public:

			ImageManager();
			
			sf::Sprite LoadNewImage( const std::string& fileName);
			sf::Sprite LoadNewImage( const char fileName[] );
			void Reset();
		};
	}
}