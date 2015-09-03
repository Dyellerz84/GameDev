#pragma once

#include "Global Functions.h"
#include "Button State Enum.h"

namespace MOO
{
	namespace UI
	{
		namespace Buttons
		{
			template<class EventEnum>
			class EventButtonInterface
			{

			private:

				sf::Sprite buttonSprite;

			public: //data
				
				EventEnum buttonEvent;
				sf::Sound buttonSound;
				MOO::UI::Buttons::ButtonState::State buttonState;

			public: //functions

				EventButtonInterface( sf::Sprite& setSprite, sf::Sound& setSound, MOO::UI::Buttons::ButtonState::State setButtonState, EventEnum setButtonEvent, sf::Vector2f& buttonPosition );

				sf::Sprite GetSprite();
				
				virtual bool CheckIfInside( const sf::Vector2f& mousePosition ) = 0;
			};

			template<class EventEnum, class ButtonShape>
			class EventButton : public EventButtonInterface<EventEnum>
			{
				
			private:

				ButtonShape buttonShape;
		
			public:
		
				EventButton( ButtonShape setShape, ButtonState::State setInitialButtonState, sf::Sprite& setSprite, sf::Sound& setSound, EventEnum setButtonEvent, sf::Vector2f& buttonPosition);
															
				bool CheckIfInside( const sf::Vector2f& mousePosition );
			};
		}
	}
}

template<class EventEnum>
MOO::UI::Buttons::EventButtonInterface<EventEnum>::EventButtonInterface( sf::Sprite& setSprite, sf::Sound& setSound, MOO::UI::Buttons::ButtonState::State setButtonState, EventEnum setButtonEvent, sf::Vector2f& setPosition )
{
	buttonSprite = setSprite;
	buttonState = setButtonState;
	buttonEvent = setButtonEvent;
	buttonSound = setSound;

	buttonSprite.setPosition( setPosition );
}

template<class EventEnum, class ButtonShape>
MOO::UI::Buttons::EventButton<EventEnum, ButtonShape>::EventButton( ButtonShape setShape, ButtonState::State setInitialButtonState, sf::Sprite& setSprite, sf::Sound& setSound, EventEnum setButtonEvent, sf::Vector2f& setPosition ) :
	
	EventButtonInterface( setSprite, setSound, setInitialButtonState, setButtonEvent, setPosition )
{
	buttonShape = setShape;
}

template<class EventEnum, class ButtonShape>
bool MOO::UI::Buttons::EventButton<EventEnum, ButtonShape>::CheckIfInside( const sf::Vector2f& mousePosition )
{
	return MOO::Globals::CheckIfInsideShape( buttonShape, mousePosition );
}

template<class EventEnum>
sf::Sprite MOO::UI::Buttons::EventButtonInterface<EventEnum>::GetSprite()
{
	int buttonHeight = buttonSprite.getTexture()->getSize().y / 5;

	int left = 0;
	int right = buttonSprite.getTexture()->getSize().x;
	int top = buttonState * buttonHeight;
	int bottom = buttonHeight;

	buttonSprite.setTextureRect( sf::IntRect( left, top, right, bottom ) );

	return buttonSprite;
}
