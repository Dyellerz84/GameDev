#include "particle.h"

particle::~particle()
{

}

int particle::getRadius()
{
	return int(body.circle.getRadius());
}

void particle::updateParticleData()
{
	Math::Vector temp = Math::Vector(0, 0);

	acceleration += force;
	velocity += acceleration;
	centerOfMass += velocity;
	center += velocity;

	bodies[0].circle.setPosition(center.x - bodies[0].circle.getRadius(), center.y - bodies[0].circle.getRadius());

	if (bodies.size() > 1)
	{
		for (unsigned int i = 1; i < bodies.size(); i++)
		{
			bodies[i].circle.setPosition( bodies[i].parent->circle.getRadius() + center.x - bodies[i].circle.getRadius(), 
				bodies[i].parent->circle.getRadius() + center.y - bodies[i].circle.getRadius());
		}
	}

	force = temp;	
	acceleration = temp;
}

particle particle::addParticles(particle* a)
{	
	Math::Vector momentum;
	Math::Vector velocity;

	double distance = this->getRadius() + a->getRadius();
	double theta = std::atan2((this->center.y - a->center.y), (this->center.x - a->center.x));

	momentum = (a->velocity * a->mass) + (this->velocity * this->mass);
	velocity = momentum / (a->mass + this->mass);

	a->body.bodyCenter.x = this->center.x + distance*std::cos(theta);
	a->body.bodyCenter.y = this->center.y + distance*std::sin(theta);

	a->body.parent = &body;
	a->body.circle.setPosition(a->body.bodyCenter.x - a->getRadius(), a->body.bodyCenter.y - a->getRadius());

	a->body.xOffset = int(a->body.bodyCenter.x - this->center.x);
	a->body.yOffset = int(a->body.bodyCenter.y - this->center.y);

	//this->centerOfMass.x = ((a->center.x*a->mass) + this->center.x*this->mass) / (a->mass + this->mass);
	//this->centerOfMass.y = ((a->center.y*a->mass) + this->center.y*this->mass) / (a->mass + this->mass);

	this->mass += a->mass;
	this->velocity = velocity;

	//a->body.circle.setPosition(float(this->center.x) + this->body.xOffset,
	//	float(this->center.y) + this->body.yOffset);

	this->bodies.push_back(a->body);
	this->bodies[0].circle.setFillColor(sf::Color::Red);

	return *this;
}



