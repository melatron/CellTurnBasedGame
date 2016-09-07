#ifndef __HERO_READER_H__
#define __HERO_READER_H__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class HeroReader : public cocostudio::NodeReader
{
public:
	static HeroReader* getInstance();
	static void purge();

	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif
