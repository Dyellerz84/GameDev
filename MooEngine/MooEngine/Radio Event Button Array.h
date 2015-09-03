#pragma once

#include <vector>

#include <SFML/System.hpp>

#include "Event Button Interface.h"

namespace MOO
{
	namespace UI
	{
		namespace Buttons
		{
			template<class EventEnum>
			class RadioButtonArray
			{

			private:

				std::vector<MOO::UI::Buttons::EventButtonInterface<EventEnum>*> buttons;

				MOO::UI::Buttons::EventButtonInterface<EventEnum>* currentChoice;
				MOO::UI::Buttons::EventButtonInterface<EventEnum>* currentButton;

			public:

				RadioButtonArray();
				RadioButtonArray( std::vector<MOO::UI::Buttons::EventButtonInterface<EventEnum>*> setButtons);
				~RadioButtonArray();
				
				std::vector<sf::Sprite> GetSprites();

				sf::Sound GetSound();

				bool CheckMouse( const sf::Vector2f& mousePosition, bool mouseClicked, bool mouseReleased );
			};
		}
	}
}

template<class EventEnum>
inline MOO::UI::Buttons::RadioButtonArray<EventEnum>::RadioButtonArray()
{
	currentChoice = NULL;
	currentButton = NULL;
}

template<class EventEnum>
inline MOO::UI::Buttons::RadioButtonArray<EventEnum>::RadioButtonArray( std::vector<MOO::UI::Buttons::EventButtonInterface<EventEnum>*> setButtons )
{
	buttons = setButtons;
}

template<class EventEnum>
inline MOO::UI::Buttons::RadioButtonArray<EventEnum>::~RadioButtonArray()
{
	for(unsigned int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
}

template<class EventEnum>
inline std::vector<sf::Sprite> MOO::UI::Buttons::RadioButtonArray<EventEnum>::GetSprites()
{
	std::vector<sf::Sprite> temp;

	for(unsigned int i = 0; i < buttons.size(); i++)
	{
		temp.push_back( buttons[i]->GetSprite() );
	}

	return temp;
}

template<class EventEnum>
inline sf::Sound MOO::UI::Buttons::RadioButtonArray<EventEnum>::GetSound()
{
	return currentChoice->buttonSound;
}

template<class EventEnum>
inline bool MOO::UI::Buttons::RadioButtonArray<EventEnum>::CheckMouse( const sf::Vector2f& mousePosition, bool mouseClicked, bool mouseReleased )
{
	if( currentButton != NULL )
	{
		if(mouseReleased)
		{
			if( currentButton->CheckIfInside( mousePosition ) )
			{
				currentChoice = currentButton;
				currentButton = NULL;
				currentChoice->buttonState = MOO::UI::Buttons::ButtonState::On;
				return true;
			}

			else
			{
				currentButton->buttonState = MOO::UI::Buttons::ButtonState::Normal;
				currentButton = NULL;

				return false;
			}
		}
	}

	else 
	{
		for(unsigned int i = 0; i < buttons.size(); i++)
		{
			if( buttons[i]->CheckIfInside( mousePosition ) )
			{
				if( mouseClicked && buttons[i] != currentChoice )
				{
					buttons[i]->buttonState = MOO::UI::Buttons::ButtonState::Pressed;
					currentButton = buttons[i];

					for( i; i < buttons.size(); i++ )
					{
						buttons[i]->buttonState = MOO::UI::Buttons::ButtonState::Normal;
					}
				}

				else if(buttons[i] != currentChoice)
				{
					buttons[i]->buttonState = MOO::UI::Buttons::ButtonState::MouseOver;
				}				
			}

			else
			{
				buttons[i]->buttonState = MOO::UI::Buttons::ButtonState::Normal;
			}
		}
	}

	return false;
}