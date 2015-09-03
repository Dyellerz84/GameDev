#pragma once

#include "Game State Base.h"
#include "Major Game State Enum.h"

class IntroState : public GameStateBase<MajorStates::Code>
{

private:

	bool fadeIn;
	bool fadeOut;

	sf::Clock fadeTimer;

	float fadeInTime;
	float pauseTime;
	float fadeOutTime;

	float fade;

	sf::Sprite splashImage;

public:

	IntroState(MOO::MOOEngine* setEngine);
	~IntroState();

	void HandleInput();
	void HandleLogic();
	void HandleOutput();
};