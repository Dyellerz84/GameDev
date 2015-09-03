#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "math.h"

struct _body
{
	sf::CircleShape circle;
	int xOffset;
	int yOffset;
	
	Math::Vector bodyCenter;

	_body* parent;

	_body();
	_body(int radius, int x, int y)
	{
		xOffset = 0;
		yOffset = 0;

		circle.setRadius(float(radius));
		circle.setPosition(float(x), float(y));
		circle.setFillColor(sf::Color::Blue);
	}
};

struct particle
{

	_body body;


	int mass;
	double direction; 

	std::vector<_body> bodies;
	Math::Vector position;
	Math::Vector center;
	Math::Vector centerOfMass;
	Math::Vector velocity;
	Math::Vector acceleration;
	Math::Vector force;

	sf::Vertex line[2];
	sf::Text xVel;
	sf::Text yVel;
	sf::Text _mass;
	sf::Text _direction; //Angle in Radians from the x-axis

	particle(int radius, int Mass , int xpos, int ypos, sf::Font& font) : body(radius, xpos ,ypos)
	{
		mass = Mass;
		center.x = xpos + radius;
		center.y = ypos + radius;

		position.x = xpos;
		position.y = ypos;

		centerOfMass = center;
		bodies.push_back(body);
	}

	~particle();
	
	int getRadius();
	void updateParticleData();

	particle addParticles(particle*);
};
