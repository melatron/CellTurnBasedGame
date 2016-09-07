#include "Cell.h"
#include "ActorModifier.h"

Cell::~Cell()
{
	this->removeActorModifier();
}

bool Cell::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

bool Cell::operator==(const Cell & rhs)
{
	if (this->gridPosition.col == rhs.gridPosition.col && this->gridPosition.row == rhs.gridPosition.row) {
		return true;
	} 

	return false;
}

void Cell::addNeighbour(Cell* neighbour)
{
	this->neighbors.pushBack(neighbour);
}

cocos2d::Vector<Cell*> Cell::getNeighbours() const
{
	return this->neighbors;
}

void Cell::listNeighbours() const
{
	/*CCLOG("---------------------");
	CCLOG("FOR -> col: %i row: %i)", this->gridPosition.col, this->gridPosition.row);

	Cell* current;
	int row, col;

	for (int i = 0; i < this->neighbors.size(); i++) {
		current = this->neighbors.at(i);
		row = current->gridPosition.row;
		col = current->gridPosition.col;
		CCLOG("CONNECTED WITH -> col: %i row: %i)", current->gridPosition.col, row);
	}
	CCLOG("---------------------");*/
}

void Cell::activateCell()
{
	this->isActivated = true;
	cocos2d::Sprite* hexagon = this->getChildByName<cocos2d::Sprite*>("hexagon");
	hexagon->setColor(cocos2d::Color3B::WHITE);
}
void Cell::deactivateCell()
{
	this->isActivated = false;
	cocos2d::Sprite* hexagon = this->getChildByName<cocos2d::Sprite*>("hexagon");
	hexagon->setColor(cocos2d::Color3B::RED);
}

bool Cell::getIsActivated() const
{
	return this->isActivated;
}

bool Cell::isConnectedWith(Cell* cell) const
{
	bool exists = false;
	for (int i = 0; (i < this->neighbors.size()) && !exists; i++) {
		if (cell == this->neighbors.at(i)) {
			exists = true;
		}
	}

	return exists;
}

bool Cell::isPassable() const
{
	return this->canPass;
}

void Cell::visualise()
{
	cocos2d::Sprite* hexagon = this->getChildByName<cocos2d::Sprite*>("hexagon");

	if (this->actorModifier) {
		this->actorModifier->visualise();
	} 
	else if (this->canPass) {
		hexagon->setColor(cocos2d::Color3B::RED);
	} 
	else {
		hexagon->setColor(cocos2d::Color3B::GREEN);
	}
}

void Cell::setCanPass(bool canPass)
{
	this->canPass = canPass;
}

ActorModifier* Cell::getActorModifier() const
{
	return this->actorModifier;
}

void Cell::setActorModifier(ActorModifier* buffer)
{
	this->removeActorModifier();
	this->actorModifier = buffer;
	this->visualise();
}

void Cell::removeActorModifier()
{
	delete this->actorModifier;
	this->actorModifier = nullptr;
	this->visualise();
}

void Cell::interact(GameActor* actor)
{
	if (this->actorModifier) {
		this->actorModifier->interact(actor);
	}
}

void Cell::setVisitor(GameActor* visitor)
{
	this->visitor = visitor;
}

GameActor* Cell::getVisitor() const
{
	return this->visitor;
}

