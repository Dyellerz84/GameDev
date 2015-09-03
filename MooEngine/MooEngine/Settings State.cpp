#include "Settings State.h"

#include <sstream>

SettingsState::SettingsState( MOO::MOOEngine* setEngine ) : GameStateBase ( setEngine, TitleStates::NoChange )
{
	fullScreen = true;
	updateText = true;

	systemSettings = engine->GetSystemSettings();

	mouseClicked = false;
	mouseReleased = false;

	ui.SetEventSystem( &eventSystem );
		
	videoModes = sf::VideoMode::getFullscreenModes();

	std::vector<sf::VideoMode> temp;

	for(unsigned int i = 0; i < videoModes.size(); i++)
	{
		if(videoModes[i].bitsPerPixel == 32)
		{
			temp.push_back( videoModes[i] );
		}
	}

	videoModes.clear();

	videoModes = temp;
	
	currentVideoMode = 0;

	currentMusicVolume = systemSettings->musicVolume;
	currentSoundVolume = systemSettings->soundVolume;

	settingsFont.loadFromFile("Resources/Title State/cour.ttf");

	log.open("settingslog.txt");

	log << videoModes.size() << std::endl;

	CreateUI();
}

SettingsState::~SettingsState()
{

}

void SettingsState::HandleInput()
{
	HandleSystemEvents();
	HandleGameEvents();
}

void SettingsState::HandleLogic()
{
	ui.CheckMouse( engine->GetMousePostion(), mouseClicked, mouseReleased );
}

void SettingsState::HandleOutput()
{
	if(updateText == true)
	{
		textDisplay.clear();

		sf::Text temp;

		temp.setColor(sf::Color( 255, 255, 255 ) );

		temp.setFont( settingsFont );

		temp.setCharacterSize(72);

		temp.setString("Resolution");

		temp.setPosition( MOO::Globals::gameWidth / 2 - temp.getGlobalBounds().width - 250, 350 );

		textDisplay.push_back( temp );

		temp.setString("Music Volume");

		temp.setPosition( MOO::Globals::gameWidth / 2 - temp.getGlobalBounds().width - 250, temp.getPosition().y + temp.getGlobalBounds().height + 50 );

		textDisplay.push_back( temp );

		temp.setString("Sound Volume");

		temp.setPosition( MOO::Globals::gameWidth / 2 - temp.getGlobalBounds().width - 250, temp.getPosition().y + temp.getGlobalBounds().height + 50 );

		textDisplay.push_back( temp );

		std::stringstream numberText;

		numberText << videoModes[currentVideoMode].width << " X " << videoModes[currentVideoMode].height;

		temp.setString( numberText.str() );

		temp.setPosition( textDisplay[0].getPosition().x + textDisplay[0].getGlobalBounds().width + 200, textDisplay[0].getPosition().y );

		textDisplay.push_back( temp );

		std::stringstream musicNumber;

		musicNumber << systemSettings->musicVolume;
		
		temp.setString( musicNumber.str() );

		temp.setPosition( textDisplay[1].getPosition().x + textDisplay[1].getGlobalBounds().width + 200, textDisplay[1].getPosition().y );

		textDisplay.push_back( temp );

		std::stringstream soundNumber;

		soundNumber << systemSettings->soundVolume;

		temp.setString( soundNumber.str() );

		temp.setPosition( textDisplay[2].getPosition().x + textDisplay[2].getGlobalBounds().width + 200, textDisplay[2].getPosition().y );

		textDisplay.push_back( temp );

		updateText = false;

	}
	
	for(unsigned int i = 0; i < textDisplay.size(); i++)
	{
		engine->Draw( textDisplay[i] );
	}

	log << "Getting Sprites from UI" << std::endl;

	std::vector<sf::Sprite> temp = ui.GetSprites();
	
	log << "Got " << temp.size() << " sprites from the UI to draw" << std::endl;

	for(unsigned int i = 0; i < temp.size(); i++ )
	{
		engine->Draw( temp[i] );
	}
}

void SettingsState::CreateUI()
{
	sf::Sprite tempButtonImage( engine->imageManager.LoadNewImage("Resources/Title State/LeftArrow.png") );

	sf::Sound tempButtonSound( engine->soundManager.LoadNewSound("Resources/Title State/Button Sound.wav") );

	sf::Rect<unsigned short int> buttonShape( MOO::Globals::gameWidth / 2 - 150, 350, tempButtonImage.getTexture()->getSize().x, 100 );

	sf::Vector2f buttonPosition( buttonShape.left, buttonShape.top );

	ui.AddButton( new MOO::UI::Buttons::EventButton<SettingsEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, tempButtonImage, tempButtonSound, SettingsEvents::DecrementResolution, buttonPosition ) );
	
	tempButtonImage = ( engine->imageManager.LoadNewImage("Resources/Title State/RightArrow.png") );

	buttonShape.left += 600;

	buttonPosition.x = buttonShape.left;

	ui.AddButton( new MOO::UI::Buttons::EventButton<SettingsEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, tempButtonImage, tempButtonSound, SettingsEvents::IncrementResolution, buttonPosition ) );

	CreateSliders();
}

void SettingsState::HandleGameEvents()
{
	while( eventSystem.PollEvents( gameEvent ) )
	{
		switch( gameEvent )
		{
			case SettingsEvents::DecrementResolution:

				currentVideoMode--;

				if(currentVideoMode > videoModes.size() )
				{
					currentVideoMode = videoModes.size() - 1;
				}

				updateText = true;

				log << "CurrenVideoMode Index = " << currentVideoMode << std::endl;

				break;

			case SettingsEvents::IncrementResolution:

				currentVideoMode++;

				if( currentVideoMode >= videoModes.size() )
				{
					currentVideoMode = 0;
				}

				updateText = true;

				log << "CurrenVideoMode Index = " << currentVideoMode << std::endl;

				break;

			case SettingsEvents::Quit:

				nextState = TitleStates::Quit;

				break;
		}
	}
}

void SettingsState::HandleSystemEvents()
{
	mouseReleased = false;

	while( engine->GetUserInput( userInput ) )
	{
		switch( userInput.type )
		{

			case sf::Event::KeyPressed:

				break;

			case sf::Event::KeyReleased:

				switch( userInput.key.code )
				{

					case sf::Keyboard::Escape:

						nextState = TitleStates::Quit;

					break;

				}

				break;

			case sf::Event::MouseButtonPressed:

				switch( userInput.mouseButton.button )
				{
					case sf::Mouse::Left:

						mouseClicked = true;
						
						break;						
				}

				break;

			case sf::Event::MouseButtonReleased:

				switch( userInput.mouseButton.button )
				{
					case sf::Mouse::Left:

						mouseClicked = false;
						mouseReleased = true;

						break;
				}

				break;
		}
	}
}

void SettingsState::CreateSliders()
{
	
	sf::Sprite incrementButtonImage( engine->imageManager.LoadNewImage("Resources/Title State/RightArrow.png") );
	sf::Sprite decrementButtonImage( engine->imageManager.LoadNewImage("Resources/Title State/LeftArrow.png") );
	sf::Sprite sliderBarImage( engine->imageManager.LoadNewImage("Resources/Title State/SliderBar.png") );
	sf::Sprite slideImage( engine->imageManager.LoadNewImage("Resources/Title State/Slide.png") );

	sf::Sound buttonSound( engine->soundManager.LoadNewSound("Resources/Title State/ButtonSound.wav") );

	sf::Rect<unsigned short int> buttonShape( MOO::Globals::gameWidth / 2 - 150, 450, incrementButtonImage.getTexture()->getSize().x, 100);

	sf::Vector2f position( buttonShape.left, buttonShape.top );

	slideImage.setPosition( buttonShape.left + incrementButtonImage.getTexture()->getSize().x, buttonShape.top );

	MOO::UI::Buttons::SimpleButton<sf::Rect<unsigned short int> >* decrementButton( new MOO::UI::Buttons::SimpleButton<sf::Rect<unsigned short int> >(buttonShape, MOO::UI::Buttons::ButtonState::Normal, decrementButtonImage, buttonSound, position ));
		
	buttonShape.left += ( buttonShape.width + slideImage.getTexture()->getSize().x );
	position.x = buttonShape.left;

	MOO::UI::Buttons::SimpleButton<sf::Rect<unsigned short int> >* incrementButton( new MOO::UI::Buttons::SimpleButton<sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, incrementButtonImage, buttonSound, position ) );

	buttonShape.left = slideImage.getPosition().x + ( slideImage.getTexture()->getSize().x * (currentMusicVolume / 100) );
	position.x = buttonShape.left;

	MOO::UI::Buttons::SimpleButton<sf::Rect<unsigned short int> >* sliderBar( new MOO::UI::Buttons::SimpleButton<sf::Rect<unsigned short int> >(buttonShape, MOO::UI::Buttons::ButtonState::Normal, sliderBarImage, buttonSound, position ));

	ui.AddSlider( new MOO::UI::Sliders::HorizontalSlider<unsigned short int>( &currentMusicVolume, 0, 100, incrementButton, decrementButton, sliderBar, slideImage, position, 0, 100 ) );

	log << "Sliders Created" << std::endl;
}