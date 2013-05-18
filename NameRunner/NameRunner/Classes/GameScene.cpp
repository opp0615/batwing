#include "GameScene.h"


CCScene* GameScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameScene *layer = GameScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	
	if(CCLayer::init())
	{
		
		if (! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}

		g_click = 0;
		m_character = CCSprite::create("char.png");
		this -> addChild(m_character,1);

		m_character->setAnchorPoint(ccp(0,0));
		m_character->setPosition(ccp(100,300));

		CCSprite* map1 = CCSprite::create("background1.png");
		this->addChild(map1,0);

		map1->setAnchorPoint(ccp(0,0));
		map1->setPosition(ccp(0,0));
		
		CCSprite* map2 = CCSprite::create("background2.png");
		this->addChild(map2,0);

		CCSprite* mob[5];
		g_itemManager = new itemManager();



		mob[0] = CCSprite::create("mob.png");
		this->addChild(mob[0],1);
		mob[0]->setAnchorPoint(ccp(0,0));
		mob[0]->setPosition(ccp(600,400));
		
		
		mob[1] = CCSprite::create("mob.png");
		this->addChild(mob[1],1);
		mob[1]->setAnchorPoint(ccp(0,0));
		mob[1]->setPosition(ccp(700,400));
		

		mob[2] = CCSprite::create("mob.png");
		this->addChild(mob[2],1);
		mob[2]->setAnchorPoint(ccp(0,0));
		mob[2]->setPosition(ccp(800,400));
		

		mob[3] = CCSprite::create("mob.png");
		this->addChild(mob[3],1);
		mob[3]->setAnchorPoint(ccp(0,0));
		mob[3]->setPosition(ccp(900,400));
		

		mob[4] = CCSprite::create("mob.png");
		this->addChild(mob[4],1);
		mob[4]->setAnchorPoint(ccp(0,0));
		mob[4]->setPosition(ccp(1000,400));
		
		
		map2->setAnchorPoint(ccp(0,0));
		map2->setPosition(ccp(1280,0));

		
		g_itemlist.push_back(mob[0]);
		g_itemlist.push_back(mob[1]);
		g_itemlist.push_back(mob[2]);
		g_itemlist.push_back(mob[3]);
		g_itemlist.push_back(mob[4]);

		
		g_char = new Character(m_character);
		g_map = new Map(map1,map2);

		

		this->setTouchEnabled(true);

		this->schedule(schedule_selector(GameScene::update),0.01);
	}
    return true;
}

void GameScene::update(float dt)
{
	g_map->Scrolling();
	g_char->Accel();

}

void GameScene::collisionCheck()
{
	CCPoint char_P=m_character->getPosition();
	
	for(;;)
	{
		
		if(1)
		{
			
		}

	}
}

void GameScene::ccTouchesBegan(CCSet* touches,CCEvent* evnet)
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	g_char->setClick(g_char->getClick());
	g_char->setJump(6);
}


void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

