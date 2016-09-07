#include "HealthInstantEffect.h"

HealthInstantEffect::HealthInstantEffect() : Effect(EffectsTypes::GiveHealth) {}

bool HealthInstantEffect::attackEffect(GameActor* actor)
{
	int left = actor->addHealth(this->amount);
	this->amount -= left;

	return left > 0 ? false : true;
}