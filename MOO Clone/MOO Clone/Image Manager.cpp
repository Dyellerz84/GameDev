#include "Image Manager.h"

MOO::Visual::ImageManager::ImageManager()
{
	images.clear();

	images[std::string("NoImage.png")].loadFromFile( "NoImage.png" );
}

sf::Sprite MOO::Visual::ImageManager::LoadNewImage( const std::string& fileName)
{
	if( images.find( fileName ) == images.end() )
	{
		if( images[fileName].loadFromFile( fileName ) == false)
		{
			return sf::Sprite( images[std::string("NoImage.png")] );			
		}
	}

	return sf::Sprite( images[fileName] );
}

sf::Sprite MOO::Visual::ImageManager::LoadNewImage( const char fileName[] )
{
	return LoadNewImage( std::string( fileName ) );
}

void MOO::Visual::ImageManager::Reset()
{
	images.clear();

	images[std::string("NoImage.png")].loadFromFile( "NoImage.png" );
}