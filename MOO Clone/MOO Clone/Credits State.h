#pragma once

#include "Game State Base.h"

#include "Title States Enum.h"

#include <vector>

namespace CreditsStates
{
	enum Code { NoChange, Quit };
}

class CreditsState : public GameStateBase<TitleStates::Code>
{

private:

	sf::Sprite windowBox;

	std::vector<sf::Text> credits;

	sf::Font creditsFont;

public:

	CreditsState(MOO::MOOEngine* setEngine);
	~CreditsState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};