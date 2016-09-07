#include "Zombie.h"
#include "Enemy.h"
#include "ActorModifier.h"

Zombie::Zombie()
{
	this->visionLimit = 3;
	this->maxHealth = 10;
}

int Zombie::evaluateActorModifier(ActorModifier* buff) {
	int sum = 0;
	auto effects = buff->getEffects();
	for (auto it = effects.begin(); it != effects.end(); it++) {
		sum += this->evaluateEffect(*it);
	}
	return sum;
}

int Zombie::evaluateEffect(Effect * effect)
{
	switch (effect->getType()) {
	case EffectsTypes::GiveEnergy:
		return 100;
	case EffectsTypes::GiveHealth:
		return 200;
	default:
		return 0;
	}
}

int Zombie::evaluateCell(Enemy* e, Cell* otherCell)
{
	if (otherCell->getVisitor()) {
		return otherCell->getVisitor()->getTeamID() == 1 ? 1 : 0;
	}
	else if (otherCell->getActorModifier()) {
		return this->evaluateActorModifier(otherCell->getActorModifier());
	}

	return 0;
}