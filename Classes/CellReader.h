#ifndef __GRIDCELL_READER_H__
#define __GRIDCELL_READER_H__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class CellReader : public cocostudio::NodeReader
{
public:
	static CellReader* getInstance();
	static void purge();

	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif
