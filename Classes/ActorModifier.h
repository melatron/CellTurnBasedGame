#ifndef __ActorModifier_H__
#define __ActorModifier_H__

#include "Constants.h"
#include "Effect.h";
class Cell;

class ActorModifier
{
public:
	std::vector<Effect*>& getEffects();
	ActorModifier(Cell*, const std::vector<Effect*>&);
	~ActorModifier();

	virtual void interact(GameActor*) = 0;
	virtual void visualise() = 0;
protected:
	Cell* holder;
	std::vector<Effect*> effects;
};
#endif
