#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "GameActor.h"

class DefaultCommand
{
public:
	virtual void execute(GameActor* actor) {};
};
#endif
