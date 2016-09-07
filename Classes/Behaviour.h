#ifndef  _BEHAVIOUR_H_
#define _BEHAVIOUR_H_

#include "cocos2d.h" 
#include "Cell.h"

class Enemy;

class Behaviour 
{
public:
	Behaviour();
	//Returns true if the score of the new Cell that we are valuing is better than the best Cell so far and
	//changes that value
	virtual int evaluateCell(Enemy*, Cell*);
	/*
	Can be overriden if there is something very special about making a move 
	(More than just comparing if 1 Cell is prefferable than an other)
	*/
	virtual bool lookForAMove(Enemy*);
	//Checks if the old Cell has the same value as the time it was set
	bool hasChanged(Cell*, int);

protected:
	int maxHealth = 0;
	int visionLimit = 1;

	void lookForIntrests(Cell*, int, cocos2d::Vector<Cell*>&);

private:
	//The enemy that we are looking path for
	Enemy* enemy;

	cocos2d::Vector<Cell*> pathToBestCell;
	Cell* bestCell;
	int bestCellScore = 0;

};
#endif