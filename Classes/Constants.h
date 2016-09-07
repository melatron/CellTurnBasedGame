#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__


enum Constants
{
	nodeWidth = 80,
	nodeHeight = 80,
	gridWidth = 1200,
	gridHeight = 750,
	triangleHeight = 20,
	triangleAndRectangle = 60,
	startingHealthRegen = 1,
	startingHealth = 1,
	startingEnergy = 3,
	startingEnergyRegen = 1,
	startingSpeed = 1,
	energyCostToMoveHero = 3,
	energyCostToMoveEnemy = 2,
	enemyRegenCooldown = 3,
	heroRegenCooldown = 1,
	energyCap = 12,
	healthCap = 12,

	maxBuffAmount = 5,
	buffTypes = 2,
	buffSpawnChance = 25,

	enemySpawnChance = 25
};

enum EffectsTypes
{
	GiveHealth,
	GiveEnergy
};

struct GridCoordinates {
	GridCoordinates() {
		this->row = 0;
		this->col = 0;
	}

	GridCoordinates(int row, int col) {
		this->row = row;
		this->col = col;
	}

	int row;
	int col;
};
#endif