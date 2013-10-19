#include "MainmenuScene.h"

#define strategyOffice_width 275
#define strategyOffice_height 345
#define gameSelect_width 378
#define gameSelect_height 521
#define option_width 296
#define option_height 218
#define rank_width 372
#define rank_height 272

#define strategyOffice2_width 301
#define strategyOffice2_height 370
#define gameSelect2_width 407
#define gameSelect2_height 536
#define option2_width 314
#define option2_height 324
#define rank2_width 389
#define rank2_height 281


#define tag_strategyOffice1 10
#define tag_gameSelect1 11
#define tag_option1 12
#define tage_rank1 13

#define tag_strategyOffice2 20
#define tag_gameSelect2 21
#define tag_option2 22
#define tage_rank2 23

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
			
			
			CCSprite* option = CCSprite::create("option1.png");
			option->setAnchorPoint(ccp(0,0));
			option->setPosition(ccp(970,8));
			this->addChild(option,1,tag_option1);

			CCSprite* rank = CCSprite::create("Rank1.png");
			rank->setAnchorPoint(ccp(0,0));
			rank->setPosition(ccp(10,0));
			this->addChild(rank,1,tage_rank1);

			CCSprite* stageSelect = CCSprite::create("StageSelect1.png");
			stageSelect->setAnchorPoint(ccp(0,0));
			stageSelect->setPosition(ccp(840,200));
			this->addChild(stageSelect,1,tag_gameSelect1);

			CCSprite* strategyOffice = CCSprite::create("Strategy Office1.png");
			strategyOffice->setAnchorPoint(ccp(0,0));
			strategyOffice->setPosition(ccp(169,337));
			this->addChild(strategyOffice,1,tag_strategyOffice1);


			this->setTouchEnabled(true);
			
		
	}

	return true;
}


void MainmenuScene::ccTouchesBegan(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	if( 840<=location.x && location.x<=840 + gameSelect_width && 200<=location.y && location.y<=200+gameSelect_height)
	{
		CCSprite* getter;
		getter = (CCSprite*)this->getChildByTag(tag_gameSelect1);
		this->removeChild(getter);

		CCSprite* stageSelect2 = CCSprite::create("StageSelect2.png");
		stageSelect2->setAnchorPoint(ccp(0,0));
		stageSelect2->setPosition(ccp(825,185));
		this->addChild(stageSelect2,1,tag_gameSelect2);

	}

	else if( 169<=location.x && location.x<=169 + strategyOffice_width && 337<=location.y && location.y<=337+strategyOffice_height)
	{
		CCSprite* getter;
		getter = (CCSprite*)this->getChildByTag(tag_strategyOffice1);
		this->removeChild(getter);

		CCSprite* stageSelect2 = CCSprite::create("Strategy Office2.png");
		stageSelect2->setAnchorPoint(ccp(0,0));
		stageSelect2->setPosition(ccp(157,323));
		this->addChild(stageSelect2,1,tag_strategyOffice2);

	}
	else if( 970<=location.x && location.x<=970 + option_width && 8<=location.y && location.y<=8+option_height)
	{
		CCSprite* getter;
		getter = (CCSprite*)this->getChildByTag(tag_option1);
		this->removeChild(getter);

		CCSprite* stageSelect2 = CCSprite::create("option2.png");
		stageSelect2->setAnchorPoint(ccp(0,0));
		stageSelect2->setPosition(ccp(960,0));
		this->addChild(stageSelect2,1,tag_option2);

	}
	else if( 10<=location.x && location.x<=10 + rank_width && 0<=location.y && location.y<=0+rank_height)
	{
		CCSprite* getter;
		getter = (CCSprite*)this->getChildByTag(tage_rank1);
		this->removeChild(getter);

		CCSprite* stageSelect2 = CCSprite::create("Rank2.png");
		stageSelect2->setAnchorPoint(ccp(0,0));
		stageSelect2->setPosition(ccp(2,0));
		this->addChild(stageSelect2,1,tage_rank2);

	}
}
void MainmenuScene::ccTouchesEnded(CCSet* touches,CCEvent* event)
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	CCSprite* getter[4];
	int remover_index=10;

	for(int i=0;i<4;i++)
	{
		getter[i]= (CCSprite*)this->getChildByTag(tag_strategyOffice2+i);
	}
	
	for(int i=0;i<4;i++)
	{
		if(getter[i] !=NULL)
		{
			remover_index = i;
		}
	}


	if(remover_index ==0)
	{
		this->removeChild(getter[remover_index]);

		CCSprite* strategyOffice = CCSprite::create("Strategy Office1.png");
		strategyOffice->setAnchorPoint(ccp(0,0));
		strategyOffice->setPosition(ccp(169,337));
		this->addChild(strategyOffice,1,tag_strategyOffice1);
	}

	if(remover_index ==1)
	{
		this->removeChild(getter[remover_index]);
		CCSprite* stageSelect = CCSprite::create("StageSelect1.png");
		stageSelect->setAnchorPoint(ccp(0,0));
		stageSelect->setPosition(ccp(840,200));
		this->addChild(stageSelect,1,tag_gameSelect1);
	}
	if(remover_index ==2)
	{
		this->removeChild(getter[remover_index]);
		CCSprite* option = CCSprite::create("option1.png");
		option->setAnchorPoint(ccp(0,0));
		option->setPosition(ccp(970,8));
		this->addChild(option,1,tag_option1);
	}
	if(remover_index ==3)
	{
		this->removeChild(getter[remover_index]);
		CCSprite* rank = CCSprite::create("Rank1.png");
		rank->setAnchorPoint(ccp(0,0));
		rank->setPosition(ccp(10,0));
		this->addChild(rank,1,tage_rank1);
	}


	if( 825<=location.x && location.x<=825 + gameSelect_width && 185<=location.y && location.y<=185+gameSelect_height)
	{
		CCScene *pScene = GameSelectScene::scene();
		 CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		 CCDirector::sharedDirector()->replaceScene(pTran);
	}

	else if( 157<=location.x && location.x<=157 + strategyOffice_width && 323<=location.y && location.y<=323+strategyOffice_height)
	{
		CCScene *pScene = StrategyOfficeScene::scene();
		CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
		CCDirector::sharedDirector()->replaceScene(pTran);

	}
	else if( 960<=location.x && location.x<=960 + option_width && 0<=location.y && location.y<=0+option_height)
	{
		

	}
	else if( 2<=location.x && location.x<=2 + rank_width && 0<=location.y && location.y<=0+rank_height)
	{
		
	}

}