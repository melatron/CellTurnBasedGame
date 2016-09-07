#include "GameActor.h"
#include "Cell.h"

bool GameActor::move(Cell* moveTo)
{	
	if (moveTo && moveTo->isPassable() && this->energy >= this->energyCostToMove) {
		this->current->setVisitor(nullptr);
		this->current->setCanPass(true);
		this->current = moveTo;
		this->current->setVisitor(this);
		this->current->setCanPass(false);

		this->walkPath.erase(0);

		this->canvasPosition = this->current->getCanvasPos();
		this->gridPosition.col = this->current->getGridPos().col;
		this->gridPosition.row = this->current->getGridPos().row;
		this->setPosition(this->canvasPosition);
		this->energy -= this->energyCostToMove;

		return true;
	}

	return false;
}

Cell* GameActor::getCurrent() const
{
	return this->current;
}

void GameActor::setCurrent(Cell* current)
{
	this->current = current;
}

bool GameActor::getIsMoving() const
{
	return this->isMoving;
}

void GameActor::setIsMoving(bool move)
{
	this->isMoving = move;
}

bool GameActor::getIsDead() const
{
	return this->isDead;
}

void GameActor::setIsDead(bool isDead)
{
	this->isDead = isDead;

	if (this->isDead) {
		this->clearPaths();
		this->current->setVisitor(nullptr);
		this->current->setCanPass(true);
		this->health = 0;
		this->energy = 0;
	}
}

int GameActor::getSpeed() const
{
	return this->speed;
}

void GameActor::setSpeed(int speed)
{
	if (speed >= 0) {
		this->speed = speed;
	}
}

int GameActor::addEnergy(int energy)
{
	int energyCap = Constants::energyCap;
	int newEnergy = this->energy + energy;

	this->energy = std::min(energyCap, newEnergy);

	return std::max(0, newEnergy - energyCap);
}

int GameActor::addHealth(int health)
{
	int healthCap = Constants::healthCap;
	int newHealth = this->health + health;

	this->health = std::min(healthCap, newHealth);

	return std::max(0, newHealth - healthCap);
}

int GameActor::getEnergy() const
{
	return this->energy;
}

int GameActor::getHealth() const
{
	return this->health;
}

int GameActor::getTeamID() const
{
	return this->teamID;
}

void GameActor::setEnergy(int energy)
{
	this->energy = energy;
}

void GameActor::setHealth(int health)
{
	this->health = health;
}

void GameActor::onEnter()
{
	this->energyLabel = this->getChildByName<cocos2d::ui::Text*>("energy");
	this->healthLabel = this->getChildByName<cocos2d::ui::Text*>("health");
}

void GameActor::showStats()
{
	this->energyLabel->setString(std::string(cocos2d::String::createWithFormat("%d", this->energy)->getCString()));
	this->healthLabel->setString(std::string(cocos2d::String::createWithFormat("%d", this->health)->getCString()));
}

void GameActor::regenerate()
{
	this->healthCooldownTracker++;
	this->energyCooldownTracker++;

	if (this->healthCooldownTracker >= this->healthCooldown) {
		this->health = std::min(this->health + this->healthRegen, this->healthCap);
		this->healthCooldownTracker = 0;
	}
	if (this->energyCooldownTracker >= this->energyCooldown) {
		this->energy = std::min(this->energy + this->energyRegen, this->energyCap);
		this->energyCooldownTracker = 0;
	}
}

Cell* GameActor::getNextCell()
{
	Cell* result;
	if (this->walkPath.size() > 0) {
		result = this->walkPath.front();
		return result;
	}
	return nullptr;
}