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

		global_mapSet = 1;
		m_scrollSpeed = 100;

		m_touchBegin = ccp(0,0);
		m_touchEnd = ccp(0,0);
		m_moveVector = ccp(0,0);

		CCSprite * background = CCSprite::create("131001_StageSelect.png");
		background->setAnchorPoint(ccp(0,0));
		background->setPosition(ccp(0,0));
		this->addChild(background,1);


		m_stage[0] = CCSprite::create("S_Stage1.png");
		m_stageSelect[0] = CCSprite::create("S_select_1.png");

		m_stage[1] = CCSprite::create("S_Stage2.png");
		m_stageSelect[1] = CCSprite::create("S_select_2.png");

		m_stage[2] = CCSprite::create("S_Stage3.png");
		m_stageSelect[2] = CCSprite::create("S_select_3.png");

		m_stage[3] = CCSprite::create("S_Stage4.png");
		m_stageSelect[3] = CCSprite::create("S_select_4.png");

		for(int i=0;i<4;i++)
		{
			m_stage[i]->setAnchorPoint(ccp(0,0));
			m_stage[i]->setPosition(ccp(425+1280*i,160));
			this->addChild(m_stage[i],2);

			
			m_stageSelect[i]->setAnchorPoint(ccp(0,0));
			m_stageSelect[i]->setPosition(ccp(340+1280*i,0));
			this->addChild(m_stageSelect[i],2);

		}


		CCSprite * stageSelect = CCSprite::create("Stage_Select_130926.png");
		stageSelect->setAnchorPoint(ccp(0,0));
		stageSelect->setPosition(ccp(240,650));
		this->addChild(stageSelect,2);


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
	m_touchBegin = location;
	if( 50<=location.x && location.x<=50 + backScene_width && 0<=location.y && location.y<=0+backScene_height)
	{
		CCSprite* getter;
		getter = (CCSprite*)this->getChildByTag(tag_backScene);

		CCActionInterval* buttonPop = CCScaleTo::create(0.1,1.2,1.2);

		getter->runAction(buttonPop);

		
	}
}


void GameSelectScene::ccTouchesEnded(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());

	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	m_touchEnd=location;

	m_moveVector = m_touchEnd-m_touchBegin;

	if(sqrt(m_moveVector.dot(m_moveVector))<200)
	{
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

	else{
		scrollSprite();
		CCLog("%d",global_mapSet);
	}
}


void GameSelectScene::scrollSprite()
{
	if(m_moveVector.x>0)
	{
		if(0< m_stage[0]->getPositionX()  && m_stage[0]->getPositionX() <1280)
		{
			global_mapSet = 1;
			return;
		}

		global_mapSet--;
		for(int i=0;i<4;i++)
		{
			CCPoint pointTemp =m_stage[i]->getPosition() ;
			m_stage[i]->setPosition(ccp(pointTemp.x+1280,pointTemp.y));

			pointTemp=m_stageSelect[i]->getPosition();
			m_stageSelect[i]->setPosition(ccp(pointTemp.x+1280,pointTemp.y));

		}


	}

	else
	{
		if(0< m_stage[3]->getPositionX() && m_stage[3]->getPositionX() <1280)
		{
			global_mapSet = 4;
			return;
		}

		global_mapSet++;
		for(int i=0;i<4;i++)
		{
			CCPoint pointTemp =m_stage[i]->getPosition() ;
			m_stage[i]->setPosition(ccp(pointTemp.x-1280,pointTemp.y));

			pointTemp=m_stageSelect[i]->getPosition();
			m_stageSelect[i]->setPosition(ccp(pointTemp.x-1280,pointTemp.y));

		}

	}

}
