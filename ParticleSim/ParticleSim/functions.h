#pragma once
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cmath>
#include "particle.h"
#include "math.h"

namespace fn
{
	const double gravConst = 0.067;

	Math::Vector generateGravity(particle*, particle*);

	double squareDist(particle*, particle*);
};

namespace collision
{
	bool checkForCollision(particle*, particle*);
	int distance(sf::CircleShape, particle*);
};

#endif