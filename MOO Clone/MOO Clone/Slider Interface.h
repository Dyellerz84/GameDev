#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Simple Button.h"

namespace MOO
{
	namespace UI
	{
		namespace Sliders
		{
			class SliderInterface
			{

			protected:

				MOO::UI::Buttons::SimpleButtonInterface* currentButton;

				MOO::UI::Buttons::SimpleButtonInterface* incrementButton;
				MOO::UI::Buttons::SimpleButtonInterface* decrementButton;
				MOO::UI::Buttons::SimpleButtonInterface* sliderBar;

				sf::Sprite slideImage;

				unsigned int upperBound;
				unsigned int lowerBound;
		
			public:

				SliderInterface( MOO::UI::Buttons::SimpleButtonInterface* setIncrementButton, MOO::UI::Buttons::SimpleButtonInterface* setDecrementButton, MOO::UI::Buttons::SimpleButtonInterface* setSliderBar, sf::Sprite& setSlideImage, sf::Vector2f& setPosition, unsigned int lowerBound, unsigned int upperBound);

				virtual bool CheckMouse( const sf::Vector2f& mousePosition, bool mouseClicked, bool mouseReleased ) = 0;

				std::vector<sf::Sprite> GetSprites();
			};

			template<class TargetAttribute>
			class HorizontalSlider : public SliderInterface
			{

			private:

				TargetAttribute* target;

				TargetAttribute targetMinimumValue;
				TargetAttribute targetMaximumValue;

			public:

				HorizontalSlider( TargetAttribute* setTarget, TargetAttribute minimumValue, TargetAttribute maximumValue, MOO::UI::Buttons::SimpleButtonInterface* setIncrementButton, MOO::UI::Buttons::SimpleButtonInterface* setDecrementButton, MOO::UI::Buttons::SimpleButtonInterface* setSliderBar, sf::Sprite& setSlideImage, sf::Vector2f& setPosition, unsigned int setLowerBound, unsigned int setUpperBound);

				bool CheckMouse( const sf::Vector2f& mousePosition, bool mouseClicked, bool mouseReleased );
			};
		}
	}
}

inline MOO::UI::Sliders::SliderInterface::SliderInterface( MOO::UI::Buttons::SimpleButtonInterface* setIncrementButton, MOO::UI::Buttons::SimpleButtonInterface* setDecrementButton, MOO::UI::Buttons::SimpleButtonInterface* setSliderBar, sf::Sprite& setSlideImage, sf::Vector2f& setPosition, unsigned int setLowerBound, unsigned int setUpperBound)
{
	incrementButton = setIncrementButton;
	decrementButton = setDecrementButton;
	sliderBar = setSliderBar;

	currentButton = NULL;

	slideImage = setSlideImage;
	
	lowerBound = setLowerBound;
	upperBound = setUpperBound;
}

inline std::vector<sf::Sprite> MOO::UI::Sliders::SliderInterface::GetSprites()
{
	std::vector<sf::Sprite> temp;

	temp.push_back( slideImage );
	temp.push_back( sliderBar->GetSprite() );
	temp.push_back( incrementButton->GetSprite() );
	temp.push_back( decrementButton->GetSprite() );

	return temp;
}

template<class TargetAttribute>
inline MOO::UI::Sliders::HorizontalSlider<TargetAttribute>::HorizontalSlider( TargetAttribute* setTarget, TargetAttribute setMinimumValue, TargetAttribute setMaximumValue, MOO::UI::Buttons::SimpleButtonInterface* setIncrementButton, MOO::UI::Buttons::SimpleButtonInterface* setDecrementButton, MOO::UI::Buttons::SimpleButtonInterface* setSliderBar, sf::Sprite& setSlideImage, sf::Vector2f& setPosition, unsigned int setLowerBound, unsigned int setUpperBound)
	: SliderInterface( setIncrementButton, setDecrementButton, setSliderBar, setSlideImage, setPosition, setLowerBound, setUpperBound )
{
	target = setTarget;

	targetMaximumValue = setMaximumValue;
	targetMinimumValue = setMinimumValue;
}

template<class TargetAttribute>
inline bool MOO::UI::Sliders::HorizontalSlider<TargetAttribute>::CheckMouse( const sf::Vector2f& mousePosition, bool mouseClicked, bool mouseReleased )
{
	if( currentButton != NULL )
	{
		if( mouseReleased == true )
		{
			if( currentButton->CheckIfInside( mousePosition ) )
			{			
				if( currentButton == incrementButton )
				{
					target++;

					if( *target > targetMaximumValue )
					{
						*target = targetMaximumValue;
					}
				}	

				else if( currentButton == decrementButton )
				{
					target--;

					if( *target < targetMinimumValue )
					{
						*target = targetMinimumValue;
					}
				}

				else if( currentButton == sliderBar )
				{
					if( mousePosition.x > slideImage.getPosition().x || mousePosition.x < slideImage.getPosition().x + slideImage.getTexture()->getSize().x )
					{
						float percentage = mousePosition.x - lowerBound;
						percentage = percentage / ( upperBound - lowerBound );
					}

					else if( mousePosition.x < slideImage.getPosition().x )
					{
						*target = targetMinimumValue;
					}

					else if(mousePosition.x > slideImage.getPosition().x + slideImage.getTexture()->getSize().x)
					{
						*target = targetMaximumValue;
					}
				}
			}

			else
			{
				currentButton->buttonState = MOO::UI::Buttons::ButtonState::Normal;
				currentButton = NULL;
			}
		}
	}

	else
	{
		if( incrementButton->CheckIfInside( mousePosition ) )
		{
			if( mouseClicked == true )
			{
				incrementButton->buttonState = MOO::UI::Buttons::ButtonState::Pressed;
				currentButton = incrementButton;
			}			

			else
			{
				incrementButton->buttonState = MOO::UI::Buttons::ButtonState::MouseOver;
			}
		}

		else if( decrementButton->CheckIfInside( mousePosition ) )
		{
			incrementButton->buttonState = MOO::UI::Buttons::ButtonState::Normal;

			if( mouseClicked == true )
			{
				decrementButton->buttonState = MOO::UI::Buttons::ButtonState::Pressed;
				currentButton = decrementButton;
			}			

			else
			{
				decrementButton->buttonState = MOO::UI::Buttons::ButtonState::MouseOver;
			}
		}

		else if( sliderBar->CheckIfInside( mousePosition ) )
		{
			incrementButton->buttonState = MOO::UI::Buttons::ButtonState::Normal;
			decrementButton->buttonState = MOO::UI::Buttons::ButtonState::Normal;

			if( mouseClicked == true )
			{
				sliderBar->buttonState = MOO::UI::Buttons::ButtonState::Pressed;
				currentButton = decrementButton;
			}			

			else
			{
				sliderBar->buttonState = MOO::UI::Buttons::ButtonState::MouseOver;
			}
		}

		else
		{
			incrementButton->buttonState = MOO::UI::Buttons::ButtonState::Normal;
			decrementButton->buttonState = MOO::UI::Buttons::ButtonState::Normal;
			sliderBar->buttonState = MOO::UI::Buttons::ButtonState::Normal;
		}
	}

	if( currentButton == NULL)
	{
		return false;
	}

	else
	{
		return true;
	}
}