#include "functions.h"

double fn::squareDist(particle* a, particle* b)
{
	double dist = (b->centerOfMass.x - a->centerOfMass.x) * (b->centerOfMass.x - a->centerOfMass.x) +
		(b->centerOfMass.y - a->centerOfMass.y) * (b->centerOfMass.y - a->centerOfMass.y);
	return dist;
};

Math::Vector fn::generateGravity(particle* a, particle* b)
{
	double gForce; //force due to gravity
	double theta;  //angle between two points
	Math::Vector force;
	std::string temp;

	gForce = fn::gravConst * ((a->mass * b->mass) / fn::squareDist(a, b));	
	theta = std::atan2((b->centerOfMass.y - a->centerOfMass.y), (b->centerOfMass.x - a->centerOfMass.x));

	force.x = gForce * std::cos(theta);
	force.y = gForce * std::sin(theta);

	return force;
};

bool collision::checkForCollision(particle* a, particle* b)
{
	bool collide;

	for (unsigned int i = 0; i < a->bodies.size(); i++)
	{	
		return collision::distance(a->bodies[i].circle, b) <= ((a->getRadius() + b->getRadius()) * (a->getRadius() + b->getRadius()));
	}
	return collide = false;
}


int collision::distance(sf::CircleShape body, particle* temp)
{
	int bodyRad = body.getRadius();
	
	Math::Vector bodyCenter = Math::Vector(body.getPosition().x + body.getRadius(), body.getPosition().y + body.getRadius());

	return (((bodyCenter.x - temp->center.x) * (bodyCenter.x - temp->center.x)) +
		((bodyCenter.y - temp->center.y )) * ((bodyCenter.y - temp->center.y)));
}

