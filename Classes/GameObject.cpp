#include "GameObject.h"

GridCoordinates GameObject::getGridPos() const
{
	return this->gridPosition;
}

void GameObject::setGridPos(GridCoordinates gridPos)
{
	this->gridPosition.col = gridPos.col;
	this->gridPosition.row = gridPos.row;
	float xx, yy;

	if (this->gridPosition.row % 2 == 0) {
		xx = (float)(gridPos.col * Constants::nodeWidth);
	}
	else {
		xx = (float)(gridPos.col * Constants::nodeWidth) + (float)(Constants::nodeWidth / 2);
	}

	yy = (float)( (gridPos.row * Constants::nodeHeight) - (gridPos.row * Constants::triangleHeight) );
	this->canvasPosition = cocos2d::Vec2(xx, yy);
	this->setPosition(this->canvasPosition);
}

cocos2d::Vec2 GameObject::getCanvasPos() const
{
	return this->canvasPosition;
}