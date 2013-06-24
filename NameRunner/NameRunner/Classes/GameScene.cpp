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
		m_character = CCSprite::create("duck.png");
		this -> addChild(m_character,1);

		m_character->setAnchorPoint(ccp(0,0));
		m_character->setPosition(ccp(100,180));

		CCSprite* map1 = CCSprite::create("back1.png");
		this->addChild(map1,0);

		map1->setAnchorPoint(ccp(0,0));
		map1->setPosition(ccp(0,0));
		
		CCSprite* map2 = CCSprite::create("back2.png");
		this->addChild(map2,0);

		map2->setAnchorPoint(ccp(0,0));
		map2->setPosition(ccp(1280,0));

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
	createItem();
	itemScrolling();
	collisionCheck();
}

void GameScene::collisionCheck()
{
	CCPoint char_P=m_character->getPosition();
	int n;
	CCSprite* char_temp;
	CCSprite* temp;
	CCPoint char_p;
	CCPoint item_P;
	char_temp = g_char->getChar();
	char_P = char_temp->getPosition();
	n = (int)g_itemlist.size();

	for(g_item_iterator = g_itemlist.begin(); g_item_iterator != g_itemlist.end(); g_item_iterator++)
	{

		temp = *(g_item_iterator);
		item_P=temp->getPosition();

		
			if(item_P.x <= char_P.x+100 &&item_P.x>=char_P.x && item_P.y >=char_P.y &&item_P.y<=char_P.y+100)
			{
				this->removeChild((*g_item_iterator));
				g_item_iterator=g_itemlist.erase(g_item_iterator);
			
			}
			
	}
		
	
}

void GameScene::itemScrolling()
{
	int n;
	CCPoint item_P;
	CCSprite* temp;
	for(g_item_iterator = g_itemlist.begin(); g_item_iterator != g_itemlist.end(); g_item_iterator++)
	{
		temp = (*g_item_iterator);
		item_P=temp->getPosition();
		temp->setPosition(ccp(item_P.x-3,item_P.y));
	}

}

void GameScene::ccTouchesBegan(CCSet* touches,CCEvent* evnet)
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	g_char->setClick(g_char->getClick());
	g_char->setJump(8);
}


void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

		
void GameScene::createItem()
{

	CCSprite* maptemp;

	
	maptemp = g_map->getMap(1);
	
	if(maptemp->getPositionX() <0&&maptemp->getPositionX()>-4)
	{
		CCSprite* item[5];

		for(int i =0;i<5;i++)
		{
			item[i] = CCSprite::create("mob.png");
			item[i]->setAnchorPoint(ccp(0,0));
			item[i]->setPosition(ccp(500+100*i,220));
			this->addChild(item[i]);

			g_itemlist.push_back(item[i]);

		}
	}

	maptemp = g_map->getMap(2);
	
	if(maptemp->getPositionX() <=1270&&maptemp->getPositionX()>-4+1270)
	{
		CCSprite* item[5];

		for(int i =0;i<5;i++)
		{
			item[i] = CCSprite::create("mob.png");
			item[i]->setAnchorPoint(ccp(0,0));
			item[i]->setPosition(ccp(500+100*i+1280,220));
			this->addChild(item[i]);

			g_itemlist.push_back(item[i]);

		}
	}
		
		
}