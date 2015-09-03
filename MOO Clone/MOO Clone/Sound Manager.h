#pragma once

#include <string>
#include <unordered_map>

#include <SFML\Audio.hpp>

namespace MOO
{
	namespace Audio
	{
		class SoundManager
		{
		
		private:

			std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

		public:

			SoundManager();
			
			sf::Sound LoadNewSound( const std::string& fileName );
			sf::Sound LoadNewSound( const char fileName[] );

			void Reset();
		};
	}
}