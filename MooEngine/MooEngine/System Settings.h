#pragma once

#include <string>

namespace MOO
{
	class SystemSettings
	{

	public:

		unsigned int screenWidth;
		unsigned int screenHeight;
		unsigned short int musicVolume;
		unsigned short int soundVolume;	

		SystemSettings();
		
		void SaveSettings();
	};
}