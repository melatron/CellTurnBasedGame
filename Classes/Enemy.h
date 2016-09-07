#ifndef  _ENEMY_H_
#define _ENEMY_H_

#include "Behaviour.h"

class Enemy : public GameActor
{
public:

 CREATE_FUNC(Enemy);

 bool init() override;
 Cell* getNextCell() override;

 void addPath(Cell*);
 void clearPaths();
 void interact();
 GameActor* click(bool);
 void setBehaviour(Behaviour*);

 //Setting new target cell its path and what was it's score in the time of setting
 void setTargetAndPath(Cell*, int, cocos2d::Vector< Cell*>);
 void clearTarget();

 int getTargetScore() const;
 int getPathSize();
 Cell* getTargetCell() const;

 bool generateRandomPath();
 std::vector<int> generateRandomPermutation(int);

protected:
	Behaviour* behaviour;
	int targetScore = 0;
	Cell* targetCell = nullptr;
};
#endif