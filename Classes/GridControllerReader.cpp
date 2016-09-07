#include "GridController.h"
#include "GridControllerReader.h"

using namespace cocos2d;

static GridControllerReader* _instanceCharacterReader = nullptr;

GridControllerReader* GridControllerReader::getInstance()
{
	if (!_instanceCharacterReader)
	{
		_instanceCharacterReader = new GridControllerReader();
	}

	return _instanceCharacterReader;
}

void GridControllerReader::purge()
{
	CC_SAFE_DELETE(_instanceCharacterReader);
}

Node* GridControllerReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	GridController* node = GridController::create();
	setPropsWithFlatBuffers(node, nodeOptions);
	
	return node;
}