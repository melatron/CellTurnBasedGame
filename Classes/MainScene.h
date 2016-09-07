#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"
#include "GridController.h"
#include "Cell.h"
#include "Constants.h"

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

	void step(float dt);
	void split(Ref* pSender, ui::Widget::TouchEventType type);

private:
	GridController* grid;
	cocos2d::Node* rootNode;

	void onEnter() override;
	void setupTouchHandling();
};

#endif // __HELLOWORLD_SCENE_H__
