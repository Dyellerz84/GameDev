#pragma once

#include <vector>

#include "Species Traits Specials Enum.h"


struct SpeciesAttributes
{
	float productionRate;
	float farmRate;
	float industryRate;
	float researchRate;

	std::vector<SpecialGeneticTraits::Trait> specialTraits;
};
