#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"
#include "Tech Tree.h"
#include "Game Event System.h"
#include "UI.h"
#include <fstream>

namespace ResearchButtonEvents
{
	enum Event{SelectNewProject, CloseWindow};
}

class ResearchState : public GameStateBase<MainGameStates::Code>
{

private:
	
	bool mouseReleased;
	bool mouseClicked;

	int curTechTier;
	int remainingCost;
	
	std::string curProject;
	std::string nextPtoject;

	//TechTree techTree;

	sf::Sprite researchWindow;

	MOO::EventSystem::EventSystem<ResearchButtonEvents::Event> eventQueue;
	MOO::UI::UI<ResearchButtonEvents::Event> ui;

public:

	ResearchState(MOO::MOOEngine* setEngine);
	~ResearchState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();



	void CreateUI();
	void CreateTree();
	int getCurTier();
};
