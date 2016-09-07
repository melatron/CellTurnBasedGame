#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"

class GameObject : public cocos2d::Node
{
public:
	//CREATE_FUNC(GameObject);

	GridCoordinates getGridPos() const;
	void setGridPos(GridCoordinates);

	cocos2d::Vec2 getCanvasPos() const;
protected:
	cocos2d::Vec2 canvasPosition;
	GridCoordinates gridPosition;
};
#endif
