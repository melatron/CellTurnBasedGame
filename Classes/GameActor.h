#ifndef __GAME_ACTOR_H__
#define __GAME_ACTOR_H__

#include "GameObject.h"
#include "ui/CocosGUI.h"

class Cell;

class GameActor : public GameObject
{
public:
	virtual void addPath(Cell*) = 0;
	virtual void clearPaths() = 0;
	virtual void interact() = 0;
	virtual GameActor* click(bool) = 0;
	virtual void regenerate();
	virtual Cell* getNextCell();

	virtual bool move(Cell*);

	Cell* getCurrent() const;
	void setCurrent(Cell*);

	bool getIsMoving() const;
	void setIsMoving(bool move);
	bool getIsDead() const;
	void setIsDead(bool isDead);

	int getSpeed() const;
	void setSpeed(int);
	int addEnergy(int);
	int addHealth(int);

	int getEnergy() const;
	int getHealth() const;
	int getTeamID() const;
	void setEnergy(int);
	void setHealth(int);

	void onEnter() override;

	void showStats();

protected:
	Cell* current;
	cocos2d::Vector<Cell*> walkPath;
	int healthRegen = Constants::startingHealthRegen;
	int health = Constants::startingHealth;
	int energy = Constants::startingEnergy;
	int energyRegen = Constants::startingEnergyRegen;
	int speed = Constants::startingSpeed;

	int energyCostToMove;
	int healthCap = Constants::healthCap;
	int energyCap = Constants::energyCap;
	int energyCooldown;
	int healthCooldown;
	int energyCooldownTracker;
	int healthCooldownTracker;

	cocos2d::ui::Text* energyLabel = this->getChildByName<cocos2d::ui::Text*>("energy");
	cocos2d::ui::Text* healthLabel = this->getChildByName<cocos2d::ui::Text*>("health");
	bool isMoving;
	bool isDead = false;
	int teamID;
};
#endif
