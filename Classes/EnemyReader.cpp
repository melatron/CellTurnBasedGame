#include "EnemyReader.h"
#include "Enemy.h"

using namespace cocos2d;

static EnemyReader* _instanceEnemyReader = nullptr;

EnemyReader* EnemyReader::getInstance()
{
   if (!_instanceEnemyReader)
{
       _instanceEnemyReader = new EnemyReader();
}
   return _instanceEnemyReader;
}

void EnemyReader::purge()
{
   CC_SAFE_DELETE(_instanceEnemyReader);
}

Node* EnemyReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
   Enemy* node = Enemy::create();
   setPropsWithFlatBuffers(node, nodeOptions);
   return node;
}
