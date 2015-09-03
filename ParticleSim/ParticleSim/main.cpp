#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <SFML/OpenGL.hpp>
#include <glm.hpp>
#include <random>
#include <cmath>
#include <chrono>
#include <fstream>
#include <string>

#include "particle.h"
#include "functions.h"


void buildParticles(unsigned int, std::vector<particle*>&, sf::Font&);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Particles");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("arial.ttf");

	unsigned int particleCount = 50;
	std::vector<particle*> particles;
	buildParticles(particleCount, particles, font);

	int loopCount = 0;
	int loop = 1;
	bool particlesAlive = false;
	bool displayData = false;

	while (window.isOpen())//start of program loop
	{
		sf::Event event;

		while (window.pollEvent(event)) //start of event polling loop
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyReleased )
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

			if (event.type == sf::Event::KeyReleased)
				if (event.key.code == sf::Keyboard::V)
					switch (displayData)
				{
					case false :
						displayData = true;
						break;
					case true :
						displayData = false;
						break;
				}
		}								//end of event polling loop

		for (unsigned int i = 0; i < particles.size(); i++)
		{
			for (unsigned int j = 0; j < particles.size(); j++)
			{
				if (j != i)
				{
					particles[i]->force += fn::generateGravity(particles[i], particles[j]);
					if (collision::checkForCollision(particles[i], particles[j]))
					{
						particles[i]->addParticles(particles[j]);
						particles.erase(particles.begin() + j);	
					}
				}
			}
		}

		for (unsigned int i = 0; i < particles.size(); i++)
			particles[i]->updateParticleData();

		window.clear();

		for (unsigned int i = 0; i < particles.size(); i++)
			for (unsigned int j = 0; j < particles[i]->bodies.size(); j++)
				window.draw(particles[i]->bodies[j].circle);

		window.display();
	}//end of program loop
}

void buildParticles(unsigned int particleCount, std::vector<particle*>& particles, sf::Font& font)
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	
	std::default_random_engine generator(seed);

	std::uniform_int_distribution<int> xpos(100, 1820);
	std::uniform_int_distribution<int> ypos(100, 980);
	std::uniform_int_distribution<int> radius(8, 10);
	std::uniform_int_distribution<int> mass(10, 20);

	for (unsigned int i = 0; i < particleCount; i++)
	{
		particle* temp = new particle(radius(generator), mass(generator), xpos(generator), ypos(generator),font);
		particles.push_back(temp);
	}
}
