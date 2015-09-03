#pragma once

#include <fstream>

#include "Game State Base.h"
#include "Main Game States Enum.h"
#include "Game Data.h"
#include "Galaxy View State Events.h"
#include "UI.h"

#include "System View State.h"
#include "Planetary Bombardment State.h"

struct GalaxySprites
{
	sf::Sprite OStarImage;
	sf::Sprite BStarImage;
	sf::Sprite AStarImage;
	sf::Sprite FStarImage;
	sf::Sprite GStarImage;
	sf::Sprite KStarImage;
	sf::Sprite MStarImage; 
};

class GalaxyViewState : public GameStateBase<MainGameStates::Code>
{

private: //data

	Game::GameData* gameData;

	float zoomFactor;
	
	sf::Vector2f cameraPosition;

	MOO::UI::UI<GalaxyViewStateEvents::Event> ui;

	std::ofstream log;

	bool mouseClicked;
	bool mouseReleased;

	StarData* systemBeingViewed;

	MOO::EventSystem::EventSystem<GalaxyViewStateEvents::Event> gameEvents;

	GalaxySprites galaxyImages;

	int xCamera;
	int yCamera;

	int previousMousex;
	int previousMousey;

	bool panningCamera;

	sf::Font gameFont;
	
	SystemViewState* systemViewState;

private: //functions
	
	void CreateUI();
	void HandleGameEvents();
	void HandleSystemEvents();

	void HandleKeyPresses();
	void HandleKeyReleases();
	void HandleMouseButtonPresses();
	void HandleMouseButtonReleases();
	void HandleMouseWheel();
	
	void DrawGalaxy();
	void DrawAnomalies();
	void DrawStars();

	void LoadImages();

	void CheckStarClick( sf::Vector2f mousePosition );

public:

	GalaxyViewState( MOO::MOOEngine* setEngine, Game::GameData* setGameData );
	~GalaxyViewState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};