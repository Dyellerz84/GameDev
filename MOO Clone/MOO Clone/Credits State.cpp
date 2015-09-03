#include "Credits State.h"

CreditsState::CreditsState(MOO::MOOEngine* setEngine) : GameStateBase<TitleStates::Code>( setEngine, TitleStates::NoChange )
{
	fullScreen = true;

	int departmentTitleTextHeight = 72;
	int nameTextHeight = 56;

	int spaceBetweenDepartments = 75;
	int spaceBetweenNames = 15;
	int spaceAfterDepartmentTitle = 35;

	windowBox = engine->imageManager.LoadNewImage("Resources/Title State/WindowBox.png");

	creditsFont.loadFromFile("Resources/Title State/cour.ttf");

	sf::Text temp( "Project Lead", creditsFont, departmentTitleTextHeight );
	temp.setStyle( sf::Text::Bold );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), 100 );
		
	credits.push_back( temp );
	
	temp.setString( "Jacob Hendricks" );
	temp.setCharacterSize( nameTextHeight );
	temp.setStyle( sf::Text::Regular );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), temp.getPosition().y + temp.getGlobalBounds().height + spaceAfterDepartmentTitle );
		
	credits.push_back( temp );

	temp.setString( "Programming Team" );
	temp.setCharacterSize( departmentTitleTextHeight );
	temp.setStyle( sf::Text::Bold );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), temp.getPosition().y + temp.getGlobalBounds().height + spaceBetweenDepartments );
		
	credits.push_back( temp );

	temp.setString( "Jacob Hendricks" );
	temp.setCharacterSize( nameTextHeight );
	temp.setStyle( sf::Text::Regular );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), temp.getPosition().y + temp.getGlobalBounds().height + spaceAfterDepartmentTitle );
		
	credits.push_back( temp );

	temp.setString( "Dan Miller" );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), temp.getPosition().y + temp.getGlobalBounds().height + spaceBetweenNames );
	
	credits.push_back( temp );

	temp.setString( "Audio Team" );
	temp.setCharacterSize( departmentTitleTextHeight );
	temp.setStyle( sf::Text::Bold );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), temp.getPosition().y + temp.getGlobalBounds().height + spaceBetweenDepartments );
		
	credits.push_back( temp );
	
	temp.setString( "Christian Hendricks" );
	temp.setCharacterSize( nameTextHeight );
	temp.setStyle( sf::Text::Regular );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), temp.getPosition().y + temp.getGlobalBounds().height + spaceAfterDepartmentTitle );
		
	credits.push_back( temp );

	temp.setString( "Visual Team" );
	temp.setCharacterSize( departmentTitleTextHeight );
	temp.setStyle( sf::Text::Bold );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), temp.getPosition().y + temp.getGlobalBounds().height + spaceBetweenDepartments );

	credits.push_back( temp );

	temp.setString( "Dan Miller" );
	temp.setCharacterSize( nameTextHeight );
	temp.setStyle( sf::Text::Regular );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), temp.getPosition().y + temp.getGlobalBounds().height + spaceAfterDepartmentTitle );
		
	credits.push_back( temp );

	temp.setString( "Jacob Hendricks" );
	temp.setPosition( (MOO::Globals::gameWidth / 2) - (temp.getGlobalBounds().width / 2), temp.getPosition().y + temp.getGlobalBounds().height + spaceBetweenNames );
	
	credits.push_back( temp );
	
}

CreditsState::~CreditsState()
{

}

void CreditsState::HandleInput()
{
	while( engine->GetUserInput( userInput ) )
	{
		if( userInput.type == sf::Event::KeyReleased || userInput.type == sf::Event::MouseButtonReleased )
		{
			nextState = TitleStates::Quit;
		}
	}
}

void CreditsState::HandleLogic()
{

}
	
void CreditsState::HandleOutput()
{
	for(unsigned int i = 0; i < credits.size(); i++)
	{
		engine->Draw( credits[i] );
	}
}