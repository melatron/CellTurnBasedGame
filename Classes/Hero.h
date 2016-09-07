#ifndef __HERO_H__
#define __HERO_H__

#include "Cell.h"
#include "Command.h"

class Hero : public GameActor
{
public:
	CREATE_FUNC(Hero);

	bool init() override;

	void addPath(Cell*);
	void clearPaths();
	void interact();
	bool move(Cell*) override;

	GameActor* split();
	GameActor* click(bool);

	void regenerate();

};
#endif
