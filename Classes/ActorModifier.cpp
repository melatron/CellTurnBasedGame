#include "ActorModifier.h"

std::vector<Effect*>& ActorModifier::getEffects()
{
	return this->effects;
}

ActorModifier::ActorModifier(Cell* holder, const std::vector<Effect*>& effects)
{
	this->holder = holder;
	this->effects = effects;

}

ActorModifier::~ActorModifier()
{
	for (int i = 0; i < this->effects.size(); i++)
	{
		delete this->effects.at(i);
	}
}
