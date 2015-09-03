#pragma once

#include <vector>

#include "Galaxy Data.h"
#include "Civilization Data.h"

namespace Game
{
	struct GameData
	{
		GalaxyData galaxy;
		std::vector<CivilizationData> civilizations;
	};
}