#include "EnergyInstantEffect.h"

EnergyInstantEffect::EnergyInstantEffect() : Effect(EffectsTypes::GiveEnergy){}

bool EnergyInstantEffect::attackEffect(GameActor* actor)
{
	int left = actor->addEnergy(this->amount);
	this->amount -= left;

	return left > 0 ? false : true;
}
