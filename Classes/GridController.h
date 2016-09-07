#ifndef __GRIDCONTROLLER_H__
#define __GRIDCONTROLLER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Cell.h"
#include "Hero.h"
#include "Constants.h"
#include "MoveCommand.h"
#include "CloneCommand.h"
#include "EnergyInstantEffect.h"
#include "HealthInstantEffect.h"
#include "ConsumedActorModifier.h"

USING_NS_CC;

class GridController : public cocos2d::Node
{
public:
	CREATE_FUNC(GridController);

	bool init() override;

	void createGrid();
	void setEdges();
	void setupTouchHandling();
	void addActor(GameActor*, Cell*);
	//void removeActor(GameActor*);

	Cell* getCellByTouchLocation(Vec2 touchLocation);
	GameActor* getActorByTouchLocation(Vec2 touchLocation);

	void spawnRandomBuff();
	void spawnRandomEnemy();

	void moveActors();
	void regenerateActors();
	void interactActors();
	void clearDeadActors();
	void checkForBattles();
	void playStep();

	Cell* getGridCellByCoordinate(int, int);

	void setSplit(bool);

protected:
	cocos2d::Vector<Cell*> nodes;
	cocos2d::Vector<GameActor*> actors;
	
	bool isSplitting = false;
	MoveCommand moveComand;
	//CloneCommand cloneComand;
};
#endif
