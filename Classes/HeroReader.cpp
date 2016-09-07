#include "HeroReader.h"
#include "Hero.h"

using namespace cocos2d;

static HeroReader* _instanceGridReader = nullptr;

HeroReader* HeroReader::getInstance()
{
	if (!_instanceGridReader)
	{
		_instanceGridReader = new HeroReader();
	}

	return _instanceGridReader;
}

void HeroReader::purge()
{
	CC_SAFE_DELETE(_instanceGridReader);
}

Node* HeroReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	Hero* node = Hero::create();
	setPropsWithFlatBuffers(node, nodeOptions);

	return node;
}