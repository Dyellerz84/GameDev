#pragma once

#include <vector>
#include <unordered_set>
#include <string>

#include "Planet Data.h"
#include "Tech Tree.h"
#include "FleetData.h"

struct CivilizationData
{
	std::unordered_set<std::string> unlockedTechs;

	PlanetData* colonizedPlanets;

	FleetData fleets;
};
