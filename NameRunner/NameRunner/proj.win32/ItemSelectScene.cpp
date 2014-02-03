#include "ItemSelectScene.h"


CCScene* ItemSelectScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        ItemSelectScene *layer = ItemSelectScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool ItemSelectScene::init()
{
	if ( CCLayer::init() )
	{

		if (! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}

		CCSprite* background = CCSprite::create("Item_select_scene.png");
		background->setAnchorPoint(ccp(0,0));
		background->setPosition(ccp(0,0));
		this->addChild(background,1);

		CCSprite* itembox = CCSprite::create("item inventory.png");
		itembox->setAnchorPoint(ccp(0,0));
		itembox->setPosition(ccp(432,421));
		this->addChild(itembox,3);

		CCSprite* itembox2 = CCSprite::create("item inventory.png");
		itembox2->setAnchorPoint(ccp(0,0));
		itembox2->setPosition(ccp(432,35));
		this->addChild(itembox2,3);

		CCSprite* itembox3 = CCSprite::create("item inventory.png");
		itembox3->setAnchorPoint(ccp(0,0));
		itembox3->setPosition(ccp(748,421));
		this->addChild(itembox3,3);




		this->setTouchEnabled(true);
	}
	return true;
}

void ItemSelectScene::ccTouchesBegan(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
}


void ItemSelectScene::ccTouchesEnded(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
}