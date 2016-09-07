#include "Hero.h"

USING_NS_CC;

bool Hero::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->isMoving = false;
	this->teamID = 1;

	this->health = Constants::startingHealth;
	this->energy = Constants::startingEnergy;
	this->energyCap = Constants::energyCap;
	this->healthCap = Constants::healthCap;
	this->energyCostToMove = Constants::energyCostToMoveHero;
	this->energyCooldown = Constants::heroRegenCooldown;
	this->healthCooldown = Constants::heroRegenCooldown;
	this->healthCooldownTracker = 0;

	return true;
}

void Hero::addPath(Cell* newCell)
{
	Cell* last;
	bool exists = false;
	int lastIndex = 0, i;
	
	if (this->walkPath.size() > 0) {
		last = this->walkPath.back();
	}
	else {
		last = this->current;
	}

	exists = last->isConnectedWith(newCell);

	if ( exists && !(newCell == this->current)) {
		newCell->activateCell();
		this->walkPath.pushBack(newCell);
		
		lastIndex = this->walkPath.size() - 1;

		for (i = lastIndex - 2; i >= lastIndex - 3 && i >= -1; i--) {
			if (i >= 0 && this->walkPath.at(i)->isConnectedWith(newCell)) {
				this->walkPath.at(lastIndex - 1)->deactivateCell();
				this->walkPath.erase(lastIndex - 1);
			}
			else if ( i == -1 && this->current->isConnectedWith(newCell) ) {
				this->walkPath.at(lastIndex - 1)->deactivateCell();
				this->walkPath.erase(lastIndex - 1);
			}
		}
	}
}

void Hero::clearPaths()
{
	Cell* current;
	
	for (int i = 0; i < this->walkPath.size(); i++) {
		current = this->walkPath.at(i);
		current->deactivateCell();
	}

	this->walkPath.clear();
}

void Hero::interact()
{
	cocos2d::Vector<Cell*> neightbours = this->current->getNeighbours();

	for (auto iter = neightbours.begin(); iter != neightbours.end(); iter++) {
		(*iter)->interact(this);
	}

	this->showStats();
}

bool Hero::move(Cell* moveTo)
{
	if (GameActor::move(moveTo)) {
		this->current->deactivateCell();
		return true;
	}
	else {
		return false;
	}
}

GameActor* Hero::split()
{
	Vector<Cell*> neightbours = this->current->getNeighbours();
	bool isPassable = false;
	Cell* current;
	int currentHeroHealth = this->getHealth();
	int currentHeroEnergy = this->getEnergy();

	for (auto iter = neightbours.begin(); iter != neightbours.end() && !isPassable; iter++) {
		current = *iter;
		if (current->isPassable()) isPassable = true;
	}
	if (isPassable) {
		Hero* hero = dynamic_cast<Hero*>(CSLoader::createNode("Hero.csb"));
		hero->setGridPos(current->getGridPos());
		hero->setCurrent(current);

		hero->setEnergy(currentHeroEnergy / 2);
		hero->setHealth(currentHeroHealth / 2);
		this->setEnergy(currentHeroEnergy / 2);
		this->setHealth(currentHeroHealth / 2);

		current->setVisitor(hero);
		current->setCanPass(false);
		return hero;
	}
}

GameActor* Hero::click(bool split)
{
	if (split) {
		return this->split();
	}
	else {
		this->setIsMoving(true);
		this->clearPaths();
	}

	return nullptr;
}

void Hero::regenerate()
{
	GameActor::regenerate();

	this->showStats();
}
