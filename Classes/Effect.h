#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "Constants.h"
#include "GameActor.h"

class Effect
{
public:
	Effect(EffectsTypes);
	virtual ~Effect() {};
	virtual bool attackEffect(GameActor*) = 0;
	EffectsTypes getType() const;
protected:
	EffectsTypes type;
};
#endif
