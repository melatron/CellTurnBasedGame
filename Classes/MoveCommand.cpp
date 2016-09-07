#include "MoveCommand.h"

void MoveCommand::execute(GameActor* actor)
{
	actor->move(actor->getNextCell());
}
