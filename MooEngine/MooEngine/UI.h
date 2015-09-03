#pragma once

#include <vector>

#include "Event Button Interface.h"
#include "Game Event System.h"
#include "Global Functions.h"
#include "Slider Interface.h"
#include "Radio Event Button Array.h"

namespace MOO
{
	namespace UI
	{
		template<class EventEnum>
		class UI
		{

		private:

			MOO::UI::Buttons::EventButtonInterface<EventEnum>* currentEventButton;
			std::vector<MOO::UI::Buttons::EventButtonInterface<EventEnum>*> eventButtons;

			MOO::UI::Sliders::SliderInterface* currentSlider;			
			std::vector<MOO::UI::Sliders::SliderInterface*> sliders;

			MOO::UI::Buttons::RadioButtonArray<EventEnum>* currentRadioMenu;
			std::vector<MOO::UI::Buttons::RadioButtonArray<EventEnum>* > radioMenus;			

			MOO::EventSystem::EventSystem<EventEnum>* eventSystem;

		public:

			UI();
			UI(MOO::EventSystem::EventSystem<EventEnum>* setEventSystem);
			~UI();

			void CheckMouse(const sf::Vector2f& mousePosition, bool mouseClicked, bool mouseReleased );
			
			std::vector<sf::Sprite> GetSprites();

			void AddButton( MOO::UI::Buttons::EventButtonInterface<EventEnum>* newEventButton );

			void AddSlider( MOO::UI::Sliders::SliderInterface* newSlider );

			void AddRadioMenu( MOO::UI::Buttons::RadioButtonArray<EventEnum> newRadioMenu );

			void SetEventSystem( MOO::EventSystem::EventSystem<EventEnum>* setEventSystem );
		};
	}
}

template<class EventEnum>
inline MOO::UI::UI<EventEnum>::UI()
{
	currentEventButton = NULL;
	currentSlider = NULL;
	currentRadioMenu = NULL;

	eventSystem = NULL;
}

template<class EventEnum>
MOO::UI::UI<EventEnum>::UI(MOO::EventSystem::EventSystem<EventEnum>* setEventSystem)
{
	currentEventButton = NULL;
	currentSlider = NULL;
	currentRadioMenu = NULL;

	eventSystem = setEventSystem;
}

template<class EventEnum>
MOO::UI::UI<EventEnum>::~UI()
{
	for(unsigned int i = 0; i < eventButtons.size(); i++)
	{
		delete eventButtons[i];
	}

	for(unsigned int i = 0; i < sliders.size(); i++)
	{
		delete sliders[i];
	}

	for(unsigned int i = 0; i < radioMenus.size(); i++)
	{
		delete radioMenus[i];
	}
}

template<class EventEnum>
void MOO::UI::UI<EventEnum>::CheckMouse( const sf::Vector2f& mousePosition, bool mouseClicked, bool mouseReleased )
{
	if(currentEventButton != NULL)
	{
		if( mouseReleased )
		{
			if( currentEventButton->CheckIfInside( mousePosition ) )
			{
				
				if( eventSystem != NULL)
				{
					eventSystem->AddEvent( currentEventButton->buttonEvent );
				}
				
				currentEventButton->buttonState = MOO::UI::Buttons::ButtonState::On;
				currentEventButton = NULL;
			}
				
			else
			{
				currentEventButton->buttonState = MOO::UI::Buttons::ButtonState::Normal;
				currentEventButton = NULL;
			}
		}
	}
	
	else if( currentSlider != NULL)
	{
		if(currentSlider->CheckMouse( mousePosition, mouseClicked, mouseReleased ) == false)
		{
			currentSlider = NULL;
		}
	}

	else if( currentRadioMenu != NULL )
	{
		if(currentRadioMenu->CheckMouse( mousePosition, mouseClicked, mouseReleased ) == false)
		{
			currentRadioMenu = NULL;
		}
	}

	else
	{
		for(unsigned int i = 0; i < eventButtons.size(); i++)
		{
			if( eventButtons[i]->buttonState != MOO::UI::Buttons::ButtonState::Disabled )
			{
				if( eventButtons[i]->CheckIfInside( mousePosition ) )
				{
					if(mouseClicked == true)
					{
						currentEventButton = eventButtons[i];
						currentEventButton->buttonState = MOO::UI::Buttons::ButtonState::Pressed;
					}

					else
					{
						eventButtons[i]->buttonState = MOO::UI::Buttons::ButtonState::MouseOver;
					}
				}

				else
				{
					eventButtons[i]->buttonState = MOO::UI::Buttons::ButtonState::Normal;
				}
			}
		}

		for(unsigned int i = 0; i < sliders.size(); i++)
		{
			if(sliders[i]->CheckMouse( mousePosition, mouseClicked, mouseReleased ) )
			{
				currentSlider = sliders[i];
			}
		}

		for(unsigned int i = 0; i < radioMenus.size(); i++)
		{
			
		}
	}
}

template<class EventEnum>
std::vector<sf::Sprite> MOO::UI::UI<EventEnum>::GetSprites()
{
	std::vector<sf::Sprite> sprites;

	for(unsigned int i = 0; i < eventButtons.size(); i++)
	{
		sprites.push_back( eventButtons[i]->GetSprite() );
	}
			
	for(unsigned int i = 0; i < sliders.size(); i++)
	{
		std::vector<sf::Sprite> temp = sliders[i]->GetSprites();
		
		for(unsigned int j = 0; j < temp.size(); j++)
		{
			sprites.push_back( temp[j] );
		}
	}

	for(unsigned int i = 0; i < radioMenus.size(); i++)
	{
		std::vector<sf::Sprite> temp = radioMenus[i]->GetSprites();
		
		for(unsigned int j = 0; j < temp.size(); j++)
		{
			sprites.push_back( temp[j] );
		}
	}

	return sprites;
}

template<class EventEnum>
inline void MOO::UI::UI<EventEnum>::AddButton( MOO::UI::Buttons::EventButtonInterface<EventEnum>* newEventButton )
{
	eventButtons.push_back( newEventButton );
}

template<class EventEnum>
inline void MOO::UI::UI<EventEnum>::SetEventSystem(  MOO::EventSystem::EventSystem<EventEnum>* setEventSystem )
{
	eventSystem = setEventSystem;
}

template<class EventEnum>
inline void MOO::UI::UI<EventEnum>::AddSlider( MOO::UI::Sliders::SliderInterface* newSlider )
{
	sliders.push_back( newSlider );
}