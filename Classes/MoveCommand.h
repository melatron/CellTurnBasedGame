#ifndef __MOVE_COMMAND_H__
#define __MOVE_COMMAND_H__

#include "Command.h"
class MoveCommand : public Command
{
public:
	virtual void execute(GameActor* actor);
};
#endif
