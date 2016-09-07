#include "Enemy.h"
#include "Zombie.h"

bool Enemy::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->isMoving = false;
	//this should be rewritten if there are more than 1 team
	this->teamID = 2;
	this->health = Constants::startingHealth;
	this->energy = Constants::startingEnergy;
	this->energyCap = Constants::energyCap;
	this->healthCap = Constants::healthCap;
	this->energyCostToMove = Constants::energyCostToMoveEnemy;
	this->energyCooldown = Constants::enemyRegenCooldown;
	this->healthCooldown = Constants::enemyRegenCooldown;
	this->healthCooldownTracker = 0;

	this->behaviour = nullptr;

	return true;
}

void Enemy::addPath(Cell* newCell)
{
	this->walkPath.pushBack(newCell);
}

void Enemy::clearPaths()
{
	this->walkPath.clear();
}

void Enemy::clearTarget()
{
	this->walkPath.clear();
	this->targetCell = nullptr;
	this->targetScore = 0;
}

void Enemy::interact()
{
	cocos2d::Vector<Cell*> neightbours = this->current->getNeighbours();

	for (auto iter = neightbours.begin(); iter != neightbours.end(); iter++) {
		(*iter)->interact(this);
	}

	//this->showStats();
}

GameActor* Enemy::click(bool split)
{
	return nullptr;
}

void Enemy::setBehaviour(Behaviour* behaviour)
{
	this->behaviour = behaviour;
}

void Enemy::setTargetAndPath(Cell* targetCell, int score, cocos2d::Vector< Cell*> path)
{
	this->targetCell = targetCell;
	this->targetScore = score;

	this->walkPath.clear();
	this->walkPath = path;
}

Cell* Enemy::getTargetCell() const
{
	return this->targetCell;
}

int Enemy::getTargetScore() const
{
	return this->targetScore;
}

int Enemy::getPathSize()
{
	return this->walkPath.size();
}

Cell* Enemy::getNextCell() {
	bool isThereANewPath = this->behaviour->lookForAMove(this);
	
	//If there is no walkPath
	if (this->walkPath.empty()){
		//but there is a target cell (The target cell is neighbour)
		if (this->targetCell)
			return nullptr;
		else
			return this->generateRandomPath() ? this->walkPath.front() : nullptr;
	}

	return this->walkPath.front();
}

//Generates random permutation from 0 to maxNum
std::vector<int> Enemy::generateRandomPermutation(int maxNum) {
	std::vector<int> order;
	for (int i = 0; i < maxNum; i++)
	{
		order.push_back(i);
	}

	std::random_shuffle(order.begin(), order.end());

	return order;
}

bool Enemy::generateRandomPath() {
	int pathSize = 5;

	CCLOG("Generating random path");
	//Creates a permutation of the indexes of the neighbours so it can check them randomly 1 by 1
	cocos2d::Vector<Cell*> neighbours = this->current->getNeighbours();
	std::vector<int> order = this->generateRandomPermutation(neighbours.size());
	Cell* nextCell = nullptr;

	//Attempts to create a path that is pathSize long
	for (int i = 0; i < pathSize; i++)
	{
		bool foundNewPath = false;
		//Goes through the random ordered neighbours of the cell that we are at the moment (this->current in the beggining)
		for (auto it = order.begin(); it != order.end(); it++)
		{
			//Takes a neighbour and checks if it can be passed and it is not already in the walk path
			Cell* currentCell = neighbours.at(*it);
			if (currentCell->isPassable() &&
				currentCell != this->current &&
				this->walkPath.find(currentCell) == this->walkPath.end())
			{
				//If it is, breaks the loop, takes new neighbours and tries to find another cell
				foundNewPath = true;
				nextCell = currentCell;
				this->addPath(nextCell);
				neighbours = nextCell->getNeighbours();
				//Makes new permutation for the new neighbours
				order = this->generateRandomPermutation(neighbours.size());
				break;
			}
		}

		//If it didn't find new cell that means it should stop looking for paths
		if (!foundNewPath) {
			i = pathSize;
		}
	}

	//If it added at least 1 new cell to the path it returns true otherwise false
	return !this->walkPath.empty();
}
