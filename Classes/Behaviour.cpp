#include "Behaviour.h"
#include "Enemy.h"

Behaviour::Behaviour() { }

//Default Behaviour
int Behaviour::evaluateCell(Enemy* enemy, Cell* newCell)
{
	return -1;
}

void Behaviour::lookForIntrests(Cell* current, int deep, cocos2d::Vector<Cell*>& pathSoFar)
{
	if (deep < 0)
	{
		return;
	}

	pathSoFar.pushBack(current);

	int currentCellScore = this->evaluateCell(this->enemy, current);
	//if the score is better or the score is the same AND with shorter path we change the new target cell
	if (this->bestCellScore < currentCellScore || (this->bestCellScore == currentCellScore && this->pathToBestCell.size()> pathSoFar.size()))
	{
		if (this->bestCellScore == currentCellScore && this->pathToBestCell.size()> pathSoFar.size())
			CCLOG("Found path with same score but shorter path");
		this->bestCell = current;
		this->bestCellScore = currentCellScore;
		this->pathToBestCell = pathSoFar;
	}

	if (!current->isPassable() && current != this->enemy->getCurrent())
	{
		pathSoFar.popBack();
		return;
	}

	for (int i = 0; i < current->getNeighbours().size(); i++)
	{
		Cell* currentCell = current->getNeighbours().at(i);
		if (pathSoFar.find(currentCell) == pathSoFar.end())
		{
			this->lookForIntrests(currentCell, deep - 1, pathSoFar);
		}
	}

	pathSoFar.popBack();

}

void printPath(cocos2d::Vector<Cell*> path) {
	CCLOG("The Path to the point is with size %i: ", path.size());
	for (int i = 0; i < path.size(); i++) {
		CCLOG("row: %i, col: %i", path.at(i)->getGridPos().row, path.at(i)->getGridPos().col);
	}
}

bool Behaviour::lookForAMove(Enemy* e)
{
	//resets information about the last best cell in the Behaviour
	this->enemy = e;
	this->pathToBestCell.clear();
	this->bestCell = e->getCurrent();
	this->bestCellScore = 0;

	//checks if the old path is still actual because the Cell that we have targeted before could
	//be changed either by an Actor moving or Buff taken or if the choice depends on our stats
	//this cell could not longer be with the same score and etc.
	if (this->enemy->getTargetCell() && hasChanged(this->enemy->getTargetCell(), this->enemy->getTargetScore())){
		CCLOG("The target cell has changed.");
		//if it has changed we clear the information we have about our target Cell
		this->enemy->clearTarget();
	}

	cocos2d::Vector<Cell*> path;
	//Look for the new best cell option and the shortest path to it
	this->lookForIntrests(e->getCurrent(), this->visionLimit + 1, path);

	CCLOG("Cell*: row: %i, col: %i", this->bestCell->getGridPos().row, this->bestCell->getGridPos().col);
	printPath(this->pathToBestCell);

	if (this->pathToBestCell.size() > 0){
		this->pathToBestCell.erase(0);
		//if it found a better score or a an equal score that has shorter path
		if (this->bestCellScore > e->getTargetScore() ||
			(this->bestCellScore == e->getTargetScore() && this->pathToBestCell.size() < e->getPathSize())) {
			if (this->bestCellScore == e->getTargetScore() && this->pathToBestCell.size() < e->getPathSize())
				CCLOG("My Score is the same but the path is shorter than the old one: ");
			else
				CCLOG("My Score is better than the old one: ");
			e->setTargetAndPath(this->bestCell, this->bestCellScore, this->pathToBestCell);
			return true;
		}
	}
	//if the best cell has not changed returns nullptr if it has returns the first cell to its path depending on its speed
	return false;
}

bool Behaviour::hasChanged(Cell* targetCell, int oldScore)
{
	return this->evaluateCell(this->enemy, targetCell) != oldScore;
}

