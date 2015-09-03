#include "Research State.h"

ResearchState::ResearchState(MOO::MOOEngine* setEngine) : GameStateBase<MainGameStates::Code>(setEngine, MainGameStates::NoChange)
{
	

	researchWindow = engine->imageManager.LoadNewImage("Resources/Main Game State/Research State/ResearchWindow.png");
	researchWindow.setPosition(MOO::Globals::gameWidth/4, MOO::Globals::gameHeight/4);
		
	fullScreen = false;
	
	mouseClicked = false;
	mouseReleased = false;

	CreateTree();
	CreateUI();
}

ResearchState::~ResearchState()
{

}

void ResearchState::HandleInput()
{

	mouseReleased = false;

	while(engine->GetUserInput( userInput ) )
	{
		if( userInput.type == sf::Event::KeyReleased )
		{
			if( userInput.key.code == sf::Keyboard::Escape )
			{
				nextState = MainGameStates::Quit;
			}
		}
		else if(userInput.type == sf::Event::MouseButtonPressed)
		{
			if( userInput.mouseButton.button == sf::Mouse::Left )
			{
				mouseClicked = true;		
			}
		}		
		else if(userInput.type == sf::Event::MouseButtonReleased)
		{
			if( userInput.mouseButton.button  == sf::Mouse::Left )
			{
				mouseClicked = false;
				mouseReleased = true;
			}
		}
	}
}

void ResearchState::HandleLogic()
{
	ui.CheckMouse( engine->GetMousePostion(), mouseClicked, mouseReleased );
}

void ResearchState::HandleOutput()
{
	std::vector<sf::Sprite> temp = ui.GetSprites();

	engine->Draw(researchWindow);

	for(unsigned int i=0;i<temp.size();i++)
	{
		engine->Draw(temp[i]);
	}
}

void ResearchState::CreateUI()
{
	ui.SetEventSystem( &eventQueue );

	sf::Rect<unsigned short int> buttonShape(((MOO::Globals::gameWidth/4)+MOO::Globals::gameWidth/2)-50,((MOO::Globals::gameHeight/4)+MOO::Globals::gameHeight/2)-50, 32, 32);
	sf::Sprite buttonSprite = engine->imageManager.LoadNewImage("Resources/Main Game State/Research State/CloseWindow.png");//need to change image path and name
	sf::Sound buttonSound = engine->soundManager.LoadNewSound("Resources/Title State/ButtonSound.wav");//need to change sound path and name

	ResearchButtonEvents::Event buttonEvent = ResearchButtonEvents::CloseWindow;
	ui.AddButton(new MOO::UI::Buttons::EventButton<ResearchButtonEvents::Event, sf::Rect<unsigned short int> >( buttonShape, MOO::UI::Buttons::ButtonState::Normal, buttonSprite, buttonSound, buttonEvent, sf::Vector2f(buttonShape.left, buttonShape.top) ) );

	sf::Rect<unsigned short int> buttonShapeNewProject(((MOO::Globals::gameWidth/4)+MOO::Globals::gameWidth/2)-105,((MOO::Globals::gameHeight/4)+MOO::Globals::gameHeight/2)-50, 32, 32);
	buttonSprite = engine->imageManager.LoadNewImage("Resources/Main Game State/Research State/NewProject.png");//need to change image path and name
	buttonSound = engine->soundManager.LoadNewSound("Resources/Title State/ButtonSound.wav");//need to change sound path and name

	buttonEvent = ResearchButtonEvents::SelectNewProject;
	ui.AddButton(new MOO::UI::Buttons::EventButton<ResearchButtonEvents::Event, sf::Rect<unsigned short int>>(buttonShapeNewProject, MOO::UI::Buttons::ButtonState::Normal, buttonSprite, buttonSound, buttonEvent, sf::Vector2f(buttonShapeNewProject.left, buttonShapeNewProject.top) ) );

}

void ResearchState::CreateTree()
{
	//std::ifstream readIn;
	//TechTree techTree;
	//std::string temp;
	//int i=0;
	//readIn.open("TechCategories.txt");

	//	while(readIn)
	//	{		
	//		//temp = readIn.get();
	//		techTree.techCategories[i].name = temp;
	//		i++;
	//	}

}