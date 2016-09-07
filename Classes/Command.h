#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "GameActor.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(GameActor* actor) = 0;
};
#endif
