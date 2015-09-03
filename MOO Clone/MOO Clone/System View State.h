#pragma once

#include "Game State Base.h"
#include "Main Game States Enum.h"
#include "Star Data.h"
#include "Galaxy View State Events.h"

struct SystemImages
{
	sf::Sprite OStarImage;
	sf::Sprite BStarImage;
	sf::Sprite AStarImage;
	sf::Sprite FStarImage;
	sf::Sprite GStarImage;
	sf::Sprite KStarImage;
	sf::Sprite MStarImage; 

	sf::Sprite toxicPlanetImage;
	sf::Sprite radiatedPlanetImage;
	sf::Sprite barrenPlanetImage;
	sf::Sprite aridPlanetImage;
	sf::Sprite tundraPlanetImage;
	sf::Sprite desertPlanetImage;
	sf::Sprite oceanPlanetImage;
	sf::Sprite swampPlanetImage;
	sf::Sprite terranPlanetImage;
	sf::Sprite paradisePlanetImage;
};

class SystemViewState : public GameStateBase<MainGameStates::Code>
{

private:
	
	SystemImages images;
	StarData* starSystem;

	sf::Font gameFont;

	bool displayPlanetData;
	unsigned short int planetDataToDisplay;

private: //functions

	void LoadImages();

public:

	SystemViewState( MOO::MOOEngine* setEngine, StarData* setStar);
	~SystemViewState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};