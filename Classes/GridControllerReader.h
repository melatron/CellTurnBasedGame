#ifndef __GRIDCONTROLLER_READER_H__
#define __GRIDCONTROLLER_READER_H__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class GridControllerReader : public cocostudio::NodeReader
{
public:
	static GridControllerReader* getInstance();
	static void purge();

	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif 
