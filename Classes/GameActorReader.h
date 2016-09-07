#ifndef __GameActor_READER_H__
#define __GameActor_READER_H__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class GameActorReader : public cocostudio::NodeReader
{
public:
	static GameActorReader* getInstance();
	static void purge();

	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif
