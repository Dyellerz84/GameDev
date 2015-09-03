#include "Sound Manager.h"

MOO::Audio::SoundManager::SoundManager()
{
	soundBuffers.clear();

	soundBuffers[std::string("NoSound.wav")].loadFromFile("NoSound.wav");
}

sf::Sound MOO::Audio::SoundManager::LoadNewSound( const std::string& fileName )
{
	if( soundBuffers.find( fileName ) == soundBuffers.end() )
	{
		if( soundBuffers[fileName].loadFromFile( fileName ) == false )
		{
			return sf::Sound( soundBuffers[std::string("NoSound.wav")] );
		}
	}

	return sf::Sound( soundBuffers[fileName] );
}

sf::Sound MOO::Audio::SoundManager::LoadNewSound( const char fileName[] )
{
	return LoadNewSound( std::string( fileName ) );
}

void MOO::Audio::SoundManager::Reset()
{
	soundBuffers.clear();

	soundBuffers[std::string("NoSound.wav")].loadFromFile("NoSound.wav");
}