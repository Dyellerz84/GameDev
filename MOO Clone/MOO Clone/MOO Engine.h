#pragma once

#include <string>

#include <SFML\Graphics.hpp>

#include "Image Manager.h"
#include "Sound Manager.h"
#include "Music Manager.h"
#include "System Settings.h"

#include "Global Constants.h"

namespace MOO
{
	class MOOEngine
	{
	
	private:
		
		std::string gameVersion;

		sf::RenderWindow app;

		MOO::SystemSettings systemSettings;

		float screenScaleX;
		float screenScaleY;
		
		float zoomFactor;

		bool useZoom;
		

	public: //data

		MOO::Visual::ImageManager imageManager;
		MOO::Audio::SoundManager soundManager;
		MOO::Audio::MusicManager musicManager;

		std::string gameToLaunch;

		bool gameIsFocus;

	public: //functions

		MOOEngine();
		~MOOEngine();

		sf::Vector2f GetMousePostion();

		void ClearScreen();

		void Draw(sf::Sprite &spriteToDraw);
		void Draw(sf::RectangleShape &rectangleToDraw);
		void Draw(sf::Text &textToDraw);
		void Draw(sf::CircleShape &circleToDraw);
		void SetZoomFactor( float setZoomFactor );
		void TurnZoomOn();
		void TurnZoomOff();
				
		void DisplayScreen();

		bool GetUserInput( sf::Event &getInput);

		void ResetAllManagers();

		std::vector<sf::VideoMode> GetAllVideoModes();

		MOO::SystemSettings* GetSystemSettings();
	};
}