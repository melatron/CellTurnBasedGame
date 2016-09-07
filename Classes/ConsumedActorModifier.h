#ifndef __CONSUMED_ActorModifier_H__
#define __CONSUMED_ActorModifier_H__

#include "ActorModifier.h"

class ConsumedActorModifier : public ActorModifier
{
public:
	ConsumedActorModifier(Cell* holder, const std::vector<Effect*>& effects);
	void interact(GameActor*);
	void visualise();
};
#endif
