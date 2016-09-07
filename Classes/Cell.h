#ifndef __CELL_H__
#define __CELL_H__

#include "Constants.h"
#include "GameActor.h"

class ActorModifier;

class Cell : public GameObject
{
public:
	CREATE_FUNC(Cell);

	~Cell();

	bool init() override;

	void addNeighbour(Cell*);
	cocos2d::Vector<Cell*> getNeighbours() const;

	void listNeighbours() const;

	void activateCell();
	void deactivateCell();

	bool getIsActivated() const;
	bool isConnectedWith(Cell* cell) const;
	bool isPassable() const;

	void visualise();
	void setCanPass(bool);

	ActorModifier* getActorModifier() const;
	void setActorModifier(ActorModifier*);
	void removeActorModifier();
	void interact(GameActor*);

	void setVisitor(GameActor*);
	GameActor* getVisitor() const;

	bool operator==(const Cell& rhs);

protected:
	cocos2d::Vector<Cell*> neighbors;

	bool isActivated = false;
	bool canPass = true;

	ActorModifier* actorModifier = nullptr;
	GameActor* visitor = nullptr;
	
	double radius = 17.0f;
};
#endif
