#pragma once

#include <vector>

#include "Ship Weapons.h"
#include "Armor Enum.h"


namespace ShipClass
{
	enum Type { ColonyShip, OutpostShip, Frigate, Destroyer, Cruiser, Battleship, Dreadnaught, Titan };
};

namespace ShipSpecials
{
	enum Special { BattlePods };
};

struct ShipArmor
{
	ArmorType::Type type;

	unsigned int frontHP;
	unsigned int leftHP;
	unsigned int rightHP;
	unsigned int rearHP;
};

struct ShipShield
{
	unsigned short int damageReduction;

	unsigned int frontHP;
	unsigned int leftHP;
	unsigned int rightHP;
	unsigned int rearHP;

	float rechargeRate;
};

struct ShipData
{
	ShipClass::Type shipClass;

	std::vector<ShipBeamWeapon> beamWeapons;

	ShipArmor armor;

	ShipShield shield;	
};