#pragma once

#include <string>
#include <vector>

struct Tech
{
	//Tech(std::string name) : name(name) {}
	std::string name;
};

struct TechTier
{
	//TechTier(std::string& techs) : techs() {}
	std::vector<Tech> techs;
	unsigned int rpCost;
};

struct TechCategory
{
	//TechCategory(std::string& name, TechTier techTiers) : name(name), techTiers() {}
	std::vector<TechTier> techTiers;
	std::string name;
	unsigned short int currentTier;
};

struct TechTree
{
	//TechTree();
	std::vector<TechCategory> techCategories;
};
