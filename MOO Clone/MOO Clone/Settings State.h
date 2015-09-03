#pragma once

#include <string>

#include "Game State Base.h"
#include "Title States Enum.h"
#include "UI.h"

#include <fstream>

namespace SettingsEvents
{
	enum Event { Quit, IncrementResolution, DecrementResolution };
}

class SettingsState : public GameStateBase<TitleStates::Code>
{

private: //data

	std::ofstream log;

	bool updateText;

	std::vector<sf::VideoMode> videoModes;

	unsigned int currentVideoMode;

	unsigned short int currentSoundVolume;
	unsigned short int currentMusicVolume;

	sf::Font settingsFont;

	std::vector<sf::Text> textDisplay;
	
	MOO::UI::UI<SettingsEvents::Event> ui;

	MOO::EventSystem::EventSystem<SettingsEvents::Event> eventSystem;
	SettingsEvents::Event gameEvent;

	MOO::SystemSettings* systemSettings;

	bool mouseClicked;
	bool mouseReleased;

private: //functions

	void CreateUI();
	void CreateSliders();
	void HandleSystemEvents();
	void HandleGameEvents();

public:
		
	SettingsState( MOO::MOOEngine* setEngine );
	~SettingsState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};