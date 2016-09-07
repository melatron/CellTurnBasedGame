#include "Effect.h"

Effect::Effect(EffectsTypes type) : type(type){}

EffectsTypes Effect::getType() const
{
	return this->type;
}
