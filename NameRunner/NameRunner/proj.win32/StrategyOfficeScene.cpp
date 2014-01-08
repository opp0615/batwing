#include "StrategyOfficeScene.h"
#include "CharacterSelectScene.h"
#include "ItemSelectScene.h"

#define backScene_width 130
#define backScene_height 130
#define heroSelect_width 477
#define heroSelect_height 420
#define itemSelect_width 398
#define itemSelect_height 419

#define tag_heroSelect 11
#define tag_itemSelect 22
#define tag_heroSelectChanged 33
#define tag_itemSelectChanged 44

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
		this->addChild(itemSelect,3,tag_itemSelect);

		CCSprite* heroSelect = CCSprite::create("hero select.png");
		heroSelect -> setAnchorPoint(ccp(0,0));
		heroSelect->setPosition(ccp(19,301));
		this->addChild(heroSelect,3,tag_heroSelect);

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

	if(19<=location.x && location.x <=19+heroSelect_width && 301<=location.y && location.y <=301 + heroSelect_height)
	{
		this->removeChildByTag(tag_heroSelect);
		CCSprite* heroSelect1 = CCSprite::create("hero select_l.png");
		heroSelect1->setAnchorPoint(ccp(0,0));
		heroSelect1->setPosition(ccp(19,301));
		this->addChild(heroSelect1,3,tag_heroSelectChanged);
	}

	else if(882<=location.x && location.x <= 882+itemSelect_width && 301<=location.y && location.y <=301 + itemSelect_height)
	{
		this->removeChildByTag(tag_itemSelect);
		CCSprite* itemSelect1 = CCSprite::create("item select_l.png");
		itemSelect1->setAnchorPoint(ccp(0,0));
		itemSelect1->setPosition(ccp(882,301));
		this->addChild(itemSelect1,3,tag_itemSelectChanged);

	}
}


void StrategyOfficeScene::ccTouchesEnded(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	if(this->getChildByTag(tag_heroSelect)==NULL)
	{
		this->removeChildByTag(tag_heroSelectChanged);
		CCSprite* heroSelect = CCSprite::create("hero select.png");
		heroSelect->setAnchorPoint(ccp(0,0));
		heroSelect->setPosition(ccp(19,301));
		this->addChild(heroSelect,3,tag_heroSelect);
		
	}

	if(this->getChildByTag(tag_itemSelect) == NULL)
	{
		this->removeChildByTag(tag_itemSelectChanged);
		CCSprite* itemSelect = CCSprite::create("item select.png");
		itemSelect -> setAnchorPoint(ccp(0,0));
		itemSelect->setPosition(ccp(882,301));
		this->addChild(itemSelect,3,tag_itemSelect);
		
	}

	if( 50<=location.x && location.x<=50 + backScene_width && 0<=location.y && location.y<=0+backScene_height)
	{
		CCScene *pScene = MainmenuScene::scene();
		CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		CCDirector::sharedDirector()->replaceScene(pTran);
	}

	else if(19<=location.x && location.x <=19+heroSelect_width && 301<=location.y && location.y <=301 + heroSelect_height)
	{
		CCScene *pScene = CharacterSelectScene::scene();
		CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		CCDirector::sharedDirector()->replaceScene(pTran);
	}

	else if(882<=location.x && location.x <= 882+itemSelect_width && 301<=location.y && location.y <=301 + itemSelect_height)
	{
		CCScene *pScene = ItemSelectScene::scene();
		CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		CCDirector::sharedDirector()->replaceScene(pTran);
	}
}