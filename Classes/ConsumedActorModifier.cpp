#include "ConsumedActorModifier.h"
#include "Cell.h"

ConsumedActorModifier::ConsumedActorModifier(Cell* holder, const std::vector<Effect*>& effects) : ActorModifier(holder, effects)
{
	this->holder->setCanPass(false);
}

void ConsumedActorModifier::interact(GameActor* actor)
{
	Effect* current;

	for (auto i = this->effects.begin(); i != this->effects.end();)
	{
		current = *i;
		if (current->attackEffect(actor))
		{
			delete *i;
			i = this->effects.erase(i);
		} else
		{
			i++;
		}
	}

	if (this->effects.empty())
	{
		this->holder->setCanPass(true);
		this->holder->removeActorModifier();
	}
}

void ConsumedActorModifier::visualise()
{
	cocos2d::Sprite* hexagon = this->holder->getChildByName<cocos2d::Sprite*>("hexagon");
	hexagon->setColor(cocos2d::Color3B::ORANGE);
}
