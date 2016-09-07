#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "CellReader.h"
#include "GridControllerReader.h"
#include "HeroReader.h"
#include "EnemyReader.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	// Register the readers for our custom classes
	// Be very careful to do CharacterReader::getInstance, not CharacterReader::getInstance() which will crash
	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("GridControllerReader", (ObjectFactory::Instance) GridControllerReader::getInstance);
	instance->registReaderObject("CellReader", (ObjectFactory::Instance) CellReader::getInstance);
	instance->registReaderObject("HeroReader", (ObjectFactory::Instance) HeroReader::getInstance);
	instance->registReaderObject("EnemyReader", (ObjectFactory::Instance) EnemyReader::getInstance);
    
    this->rootNode = CSLoader::createNode("MainScene.csb");

	Size size = Director::getInstance()->getVisibleSize();
	this->rootNode->setContentSize(size);
	ui::Helper::doLayout(this->rootNode);

	/////////////// WRITE HERE ///////////////

	

	//////////////////////////////////////////

    addChild(this->rootNode);

    return true;
}

void MainScene::onEnter()
{
	Layer::onEnter();

	this->grid = this->rootNode->getChildByName<GridController*>("grid");

	this->setupTouchHandling();


	cocos2d::ui::Button* splitButton = this->rootNode->getChildByName<cocos2d::ui::Button*>("splitButton");
	splitButton->addTouchEventListener(CC_CALLBACK_2(MainScene::split, this));


	this->schedule(CC_SCHEDULE_SELECTOR(MainScene::step), 1.0f);

}

void MainScene::split(Ref* pSender, ui::Widget::TouchEventType type)
{
	this->grid->setSplit(true);
}

void MainScene::step(float dt)
{
	this->grid->playStep();
}

void MainScene::setupTouchHandling()
{
	this->grid->setupTouchHandling();
}