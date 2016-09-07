#include "CellReader.h"
#include "Cell.h"

using namespace cocos2d;

static CellReader* _instanceGridReader = nullptr;

CellReader* CellReader::getInstance()
{
	if (!_instanceGridReader)
	{
		_instanceGridReader = new CellReader();
	}

	return _instanceGridReader;
}

void CellReader::purge()
{
	CC_SAFE_DELETE(_instanceGridReader);
}

Node* CellReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	Cell* node = Cell::create();
	setPropsWithFlatBuffers(node, nodeOptions);

	return node;
}