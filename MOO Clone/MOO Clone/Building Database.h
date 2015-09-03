#pragma once

#include <string>
#include <unordered_map>

#include "BuildingData.h"

class PlanetBuildingDatabase
{

private:

	std::unordered_map<std::string, BuildingData> building;

public:

	PlanetBuildingDatabase();

	BuildingData GetBuildingData( std::string );
}