#ifndef _ENEMY_READER_H_
#define _ENEMY_READER_H_

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h" 

class EnemyReader : public cocostudio::NodeReader
{
public:
   static EnemyReader* getInstance();
  static void purge();
  cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);


};
#endif