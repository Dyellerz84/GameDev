#pragma once

namespace DifficultyLevel
{
	enum Level { Tutor, Easy, Normal, Hard, Impossible };
}

namespace GalaxySize
{
	enum Size { Tiny, Small, Medium, Large, Huge };
}

namespace GalaxyAge
{
	enum Age { Young, Average, Old };
}

namespace StartingTechLevel
{
	enum Level { PreWarp, PostWarp, Advanced, HighlyAdvanced };
}

struct NewGameSettings
{
	unsigned short int numberOfPlayers;

	DifficultyLevel::Level difficulty;

	GalaxySize::Size galaxySize;

	GalaxyAge::Age galaxyAge;

	bool tacticalCombat;
};