#include "GameActorReader.h"
#include "GameActor.h"

using namespace cocos2d;

static GameActorReader* _instanceGridReader = nullptr;

GameActorReader* GameActorReader::getInstance()
{
	if (!_instanceGridReader)
	{
		_instanceGridReader = new GameActorReader();
	}

	return _instanceGridReader;
}

void GameActorReader::purge()
{
	CC_SAFE_DELETE(_instanceGridReader);
}

Node* GameActorReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	GameActor* node = GameActor::create();
	setPropsWithFlatBuffers(node, nodeOptions);

	return node;
}