#include "MainmenuScene.h"

CCScene* MainmenuScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MainmenuScene *layer = MainmenuScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool MainmenuScene::init()
{
	if ( CCLayer::init() )
	{

		if (! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}
		
		
			CCSprite* main = CCSprite::create("130914_main_final.png");
			main->setAnchorPoint(ccp(0,0));
			main->setPosition(ccp(0,0));
			this->addChild(main,0);
			this->setTouchEnabled(true);
			
			
			CCSprite* option = CCSprite::create("option1.png");
			option->setAnchorPoint(ccp(0,0));
			option->setPosition(ccp(970,8));
			this->addChild(option,1);

			CCSprite* rank = CCSprite::create("Rank1.png");
			rank->setAnchorPoint(ccp(0,0));
			rank->setPosition(ccp(10,0));
			this->addChild(rank,1);

			CCSprite* stageSelect = CCSprite::create("StageSelect1.png");
			stageSelect->setAnchorPoint(ccp(0,0));
			stageSelect->setPosition(ccp(840,200));
			this->addChild(stageSelect,1,11);

			CCSprite* strategyOffice = CCSprite::create("Strategy Office1.png");
			strategyOffice->setAnchorPoint(ccp(0,0));
			strategyOffice->setPosition(ccp(169,337));
			this->addChild(strategyOffice,1);
			
		
	}

	return true;
}


void MainmenuScene::ccTouchesBegan(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	if( 840<=location.x && location.x<=840 + 378 && 200<=location.y && location.y<=200+521)
	{
		CCSprite* getter;
		getter = (CCSprite*)this->getChildByTag(11);
		this->removeChild(getter);

		CCSprite* stageSelect2 = CCSprite::create("StageSelect2.png");
		stageSelect2->setAnchorPoint(ccp(0,0));
		stageSelect2->setPosition(ccp(825,185));
		this->addChild(stageSelect2,1,22);

	}
}
void MainmenuScene::ccTouchesEnded(CCSet* touches,CCEvent* event)
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	CCSprite* getter;
	getter = (CCSprite*)this->getChildByTag(22);
	
	if(getter !=NULL)
	{
		
		this->removeChild(getter);

		CCSprite* stageSelect1 = CCSprite::create("StageSelect1.png");
		stageSelect1->setAnchorPoint(ccp(0,0));
		stageSelect1->setPosition(ccp(840,200));
		this->addChild(stageSelect1,1,11);
	}
	
	if( 825<=location.x && location.x<=825 + 407 && 185<=location.y && location.y<=185+536)
	{


		 CCScene *pScene = GameScene::scene();
		 CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		 CCDirector::sharedDirector()->replaceScene(pTran);
	}

}