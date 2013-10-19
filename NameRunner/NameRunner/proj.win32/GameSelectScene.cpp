#include "GameSelectScene.h"

#define stage_width 430
#define stage_height 430
#define backScene_width 130
#define backScene_height 130

#define tag_backScene 10
CCScene* GameSelectScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameSelectScene *layer = GameSelectScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool GameSelectScene::init()
{
	if ( CCLayer::init() )
	{

		if (! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}

		CCSprite * background = CCSprite::create("131001_StageSelect.png");
		background->setAnchorPoint(ccp(0,0));
		background->setPosition(ccp(0,0));
		this->addChild(background,1);

		CCSprite * stage1 = CCSprite::create("S_Stage1.png");
		stage1->setAnchorPoint(ccp(0,0));
		stage1->setPosition(ccp(425,160));
		this->addChild(stage1,2);

		CCSprite * stageSelect = CCSprite::create("Stage_Select_130926.png");
		stageSelect->setAnchorPoint(ccp(0,0));
		stageSelect->setPosition(ccp(240,650));
		this->addChild(stageSelect,2);

		CCSprite * stage1_name = CCSprite::create("S_select_1.png");
		stage1_name->setAnchorPoint(ccp(0,0));
		stage1_name->setPosition(ccp(340,0));
		this->addChild(stage1_name,2);

		CCSprite * backScene = CCSprite::create("backscene.png");
		backScene->setAnchorPoint(ccp(0,0));
		backScene->setPosition(ccp(50,0));
		this->addChild(backScene,2,tag_backScene);

		this->setTouchEnabled(true);
	}
	
	return true;
}

void GameSelectScene::ccTouchesBegan(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	if( 50<=location.x && location.x<=50 + backScene_width && 0<=location.y && location.y<=0+backScene_height)
	{
		CCSprite* getter;
		getter = (CCSprite*)this->getChildByTag(tag_backScene);

		CCActionInterval* buttonPop = CCScaleTo::create(0.1,1.2,1.2);

		getter->runAction(buttonPop);

		CCLog("%d",getter);
	}

}


void GameSelectScene::ccTouchesEnded(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	
	if( 425<=location.x && location.x<=425 + stage_width && 160<=location.y && location.y<=160+stage_height)
	{
		CCScene *pScene = GameScene::scene();
		CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		CCDirector::sharedDirector()->replaceScene(pTran);
	}

	else if( 50<=location.x && location.x<=50 + backScene_width && 0<=location.y && location.y<=0+backScene_height)
	{
		CCScene *pScene = MainmenuScene::scene();
		CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		CCDirector::sharedDirector()->replaceScene(pTran);

		CCSprite* getter;
		getter = (CCSprite*)this->getChildByTag(tag_backScene);

		CCActionInterval* buttonPop = CCScaleTo::create(0.1,1.0,1.0);

		getter->runAction(buttonPop);
	}
}