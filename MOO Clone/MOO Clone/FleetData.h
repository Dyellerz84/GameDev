#pragma once

#include <vector>

#include "Ship Data.h"

struct FleetData
{
	std::vector<ShipData> ships;
	sf::Vector2f location;
	sf::Vector2f destination;
};