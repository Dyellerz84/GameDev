#include "System Settings.h"

#include <fstream>

MOO::SystemSettings::SystemSettings()
{
	std::ifstream fromFile("settings.txt");

	if( fromFile )
	{
		fromFile >> screenWidth;
		fromFile >> screenHeight;
		fromFile >> musicVolume;
		fromFile >> soundVolume;
	}
	
	else
	{
		screenWidth = 0;
		screenHeight = 0;
		musicVolume = 100;
		soundVolume = 100;
	}

	fromFile.close();
}
		
void MOO::SystemSettings::SaveSettings()
{
	std::ofstream toFile( "settings.txt" );

	toFile << screenWidth << std::endl;
	toFile << screenHeight << std::endl;
	toFile << musicVolume << std::endl;
	toFile << soundVolume << std::endl;
}