#ifndef __HEALTH_ENERGY_H__
#define __HEALTH_ENERGY_H__

#include "Constants.h"
#include "Effect.h"

class HealthInstantEffect : public Effect
{
public:
	HealthInstantEffect();
	bool attackEffect(GameActor*);
private:
	int amount = 2;
};
#endif
