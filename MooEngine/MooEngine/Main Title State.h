#pragma once

#include <fstream>

#include "Game State Base.h"
#include "Title States Enum.h"
#include "Game Event System.h"
#include "UI.h"

namespace MainTitleStateEvents
{
	enum Event{ StartNewGame, Continue, LoadGame, GoToSettings, GoToCredits, Quit };
}

class MainTitleState : public GameStateBase<TitleStates::Code>
{

private: //data

	std::ofstream log;

	sf::Sprite backgroundImage;

	MOO::EventSystem::EventSystem<MainTitleStateEvents::Event> eventQueue;
	
	MOO::UI::UI<MainTitleStateEvents::Event> ui;

	bool mouseClicked;
	bool mouseReleased;

private: //fucntions

	void HandleUserInput();
	void HandleGameEvents();

	void CreateUI();

public:

	MainTitleState( MOO::MOOEngine* setEngine );
	~MainTitleState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();

};