#include "CharacterSelectScene.h"

#define tag_subway 11
#define tag_ring 22
#define subway_width 300
#define subway_height 300
#define ring_width 300
#define ring_height 300


CCScene* CharacterSelectScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        CharacterSelectScene *layer = CharacterSelectScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool CharacterSelectScene::init()
{
	if ( CCLayer::init() )
	{

		if (! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}

		global_charSet = 10;
		CCSprite* background = CCSprite::create("CharacterSelect.png");
		background->setAnchorPoint(ccp(0,0));
		background->setPosition(ccp(0,0));
		this->addChild(background,1);

		CCSprite* subway = CCSprite::create("CS_subway.png");
		subway->setAnchorPoint(ccp(0,0));
		subway->setPosition(ccp(333,227));
		this->addChild(subway,3,tag_subway);

		CCSprite* ring = CCSprite::create("CS_ring.png");
		ring->setAnchorPoint(ccp(0,0));
		ring->setPosition(ccp(889,227));
		this->addChild(ring,3,tag_ring);

		CCSprite* backScene = CCSprite::create("backscene.png");
		backScene->setAnchorPoint(ccp(0,0));
		backScene->setPosition(ccp(1100,20));
		this->addChild(backScene,3);

		this->setTouchEnabled(true);
	}
	return true;
}

void CharacterSelectScene::ccTouchesBegan(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
}


void CharacterSelectScene::ccTouchesEnded(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	if(1100<=location.x && location.x<=1100 +130 && 20<=location.y&& location.y<=20+130)
	{
		CCScene *pScene = StrategyOfficeScene::scene();
		CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		CCDirector::sharedDirector()->replaceScene(pTran);
	}

	else if(333<=location.x && location.x<=333+subway_width && 227 <= location.y && location.y <= 227+subway_height)
	{
		global_charSet = 0;
	}

	else if(889<=location.x && location.x<=889+ring_width && 227<=location.y && location.y<=227+ring_height)
	{
		global_charSet = 1;
	}

	
}