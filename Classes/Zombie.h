#ifndef  _ZOMBIE_H_
#define _ZOMBIE_H_

#include "Behaviour.h"
#include "Cell.h"
class Effect;

class Zombie : public Behaviour
{
public:
	Zombie();
	int evaluateCell(Enemy*, Cell*) override;

	int evaluateActorModifier(ActorModifier*);

	int evaluateEffect(Effect*);
};
#endif