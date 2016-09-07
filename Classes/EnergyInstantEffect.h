#ifndef __EFFECT_ENERGY_H__
#define __EFFECT_ENERGY_H__

#include "Constants.h"
#include "Effect.h"

class EnergyInstantEffect: public Effect
{
public:
	EnergyInstantEffect();
	bool attackEffect(GameActor*);
private:
	int amount = 2;
};
#endif
