#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Button State Enum.h"

namespace MOO
{
	namespace UI
	{
		namespace Buttons
		{
			class SimpleButtonInterface
			{

			private:

				sf::Sprite buttonSprite;

			public: //data
				
				sf::Sound buttonSound;
				MOO::UI::Buttons::ButtonState::State buttonState;

			public: //functions

				SimpleButtonInterface( sf::Sprite& setSprite, sf::Sound& setSound, MOO::UI::Buttons::ButtonState::State setButtonState, sf::Vector2f& buttonPosition );

				sf::Sprite GetSprite();
				
				virtual bool CheckIfInside( const sf::Vector2f& mousePosition ) = 0;
			};

			template<class ButtonShape>
			class SimpleButton : public SimpleButtonInterface
			{
				
			private:

				ButtonShape buttonShape;
		
			public:
		
				SimpleButton( ButtonShape setShape, ButtonState::State setInitialButtonState, sf::Sprite& setSprite, sf::Sound& setSound, sf::Vector2f& buttonPosition);
															
				bool CheckIfInside( const sf::Vector2f& mousePosition );
			};
		}
	}
}

inline MOO::UI::Buttons::SimpleButtonInterface::SimpleButtonInterface( sf::Sprite& setSprite, sf::Sound& setSound, MOO::UI::Buttons::ButtonState::State setButtonState, sf::Vector2f& buttonPosition )
{
	buttonSprite = setSprite;
	buttonState = setButtonState;
	buttonSound = setSound;

	buttonSprite.setPosition( buttonPosition );
}

inline sf::Sprite MOO::UI::Buttons::SimpleButtonInterface::GetSprite()
{
	int buttonHeight = buttonSprite.getTexture()->getSize().y / 5;

	int left = 0;
	int right = buttonSprite.getTexture()->getSize().x;
	int top = buttonState * buttonHeight;
	int bottom = buttonHeight;

	buttonSprite.setTextureRect( sf::IntRect( left, top, right, bottom ) );

	return buttonSprite;
}

template<class ButtonShape>
inline bool MOO::UI::Buttons::SimpleButton<ButtonShape>::CheckIfInside( const sf::Vector2f& mousePosition )
{
	return MOO::Globals::CheckIfInsideShape( buttonShape, mousePosition );
}

template<class ButtonShape>
inline MOO::UI::Buttons::SimpleButton<ButtonShape>::SimpleButton( ButtonShape setShape, ButtonState::State setInitialButtonState, sf::Sprite& setSprite, sf::Sound& setSound, sf::Vector2f& buttonPosition)
	: SimpleButtonInterface( setSprite, setSound, setInitialButtonState, buttonPosition )
{
	buttonShape = setShape;
}