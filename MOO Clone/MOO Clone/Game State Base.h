#pragma once

#include "MOO Engine.h"

template<class StateEnum>
class GameStateBase
{

protected:
	
	MOO::MOOEngine *engine;

public:

	sf::Event userInput;

	bool fullScreen;
	StateEnum nextState;

	GameStateBase();
	GameStateBase(MOO::MOOEngine* setEngine, StateEnum defaultState);

	virtual ~GameStateBase();

	virtual void HandleInput() = 0;
	virtual void HandleLogic() = 0;
	virtual void HandleOutput() = 0;
};

template<class StateEnum>
inline GameStateBase<StateEnum>::GameStateBase()
{

}

template<class StateEnum>
inline GameStateBase<StateEnum>::GameStateBase(MOO::MOOEngine* setEngine, StateEnum defaultState)
{
	engine = setEngine;

	nextState = defaultState;
}

template<class StateEnum>
inline GameStateBase<StateEnum>::~GameStateBase()
{

}
