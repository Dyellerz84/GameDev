#pragma once

namespace GameDifficulty
{
	enum Difficulty{ Tutor, Easy, Normal, Hard, Impossible, OhMyGod};
}

namespace GalaxySize
{
	enum Size { Tiny, Small, Medium, Large, Huge, DoesItEverEnd };
}

namespace GalaxyAge
{
	enum Age { BrandNew, Infant, Moderate, Old, Crumbling };
}

namespace GalaxyShape
{
	enum Shape { Spiral, Ring, Elliptical, Square };
}

namespace TechLevel
{
	enum Level { PreWarp, PostWarp, Advanced, HighlyAdvanced };
}

struct NewGameSettingsData
{
	GameDifficulty::Difficulty gameDifficulty;

	GalaxySize::Size galaxySize;

	GalaxyAge::Age galaxyAge;

	GalaxyShape::Shape galaxyShape;

	TechLevel::Level startingTechLevel;

	unsigned short int numberOfPlayers;

	bool tacticalCombat;
};