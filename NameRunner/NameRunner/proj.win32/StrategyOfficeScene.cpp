#include "StrategyOfficeScene.h"

#define backScene_width 130
#define backScene_height 130

CCScene* StrategyOfficeScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        StrategyOfficeScene *layer = StrategyOfficeScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool StrategyOfficeScene::init()
{
	if ( CCLayer::init() )
	{

		if (! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}

		CCSprite* background = CCSprite::create("background.png");
		background -> setAnchorPoint(ccp(0,0));
		background->setPosition(ccp(0,0));
		this->addChild(background,1);

		CCSprite* mouse = CCSprite::create("mouse_edit.png");
		mouse -> setAnchorPoint(ccp(0,0));
		mouse->setPosition(ccp(580,58));
		this->addChild(mouse,3);

		CCSprite* itemSelect = CCSprite::create("item select.png");
		itemSelect -> setAnchorPoint(ccp(0,0));
		itemSelect->setPosition(ccp(882,301));
		this->addChild(itemSelect,2);

		CCSprite* heroSelect = CCSprite::create("hero select.png");
		heroSelect -> setAnchorPoint(ccp(0,0));
		heroSelect->setPosition(ccp(19,301));
		this->addChild(heroSelect,2);

		CCSprite* backScene = CCSprite::create("backScene.png");
		backScene -> setAnchorPoint(ccp(0,0));
		backScene->setPosition(ccp(50,0));
		this->addChild(backScene,2);

		this->setTouchEnabled(true);

	}
	return true;
}

void StrategyOfficeScene::ccTouchesBegan(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

}


void StrategyOfficeScene::ccTouchesEnded(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	if( 50<=location.x && location.x<=50 + backScene_width && 0<=location.y && location.y<=0+backScene_height)
	{
		CCScene *pScene = MainmenuScene::scene();
		CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		CCDirector::sharedDirector()->replaceScene(pTran);
	}

}