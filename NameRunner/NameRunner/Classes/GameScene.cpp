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

		game_speed = 10;

		g_click = 0;
		scroll_count = 0;
	
		mapInit();

		

		
		CCSprite* back1 = CCSprite::create("Italy_background.png");
		back1->setAnchorPoint(ccp(0,0));
		back1->setPosition(ccp(0,0));
		this->addChild(back1,0);

		CCSprite* back2 = CCSprite::create("Italy_background.png");
		back2->setAnchorPoint(ccp(0,0));
		this->addChild(back2,0);
		

		g_map = new Map(back1,back2,game_speed);
		

		charInit();
		

		this->setTouchEnabled(true);

		this->schedule(schedule_selector(GameScene::update),0.01);
	}
    return true;
}

void GameScene::update(float dt)
{
	g_map->Scrolling();
	g_char->Accel();
	//createItem();
	itemScrolling();
	//createmob();
	mobScrolling();
	//collisionCheck();
	mapScrolling();
	floorcheck();

}

void GameScene::collisionCheck()
{
	
	
	CCPoint char_P=m_character->getPosition();

	
	CCSprite* char_temp;
	CCSprite* temp;
	CCPoint char_p;
	CCPoint item_P;
	char_temp = g_char->getChar();
	char_P = char_temp->getPosition();
	

	//item collision check
	
	for(g_item_iterator = g_itemlist.begin(); g_item_iterator != g_itemlist.end(); g_item_iterator++)
	{

		temp = *(g_item_iterator);
		item_P=temp->getPosition();

		
		if(item_P.x <-20)
		{
			this->removeChild((*g_item_iterator));
			g_item_iterator=g_itemlist.erase(g_item_iterator);
			
		}
		
		if(item_P.x <= char_P.x+g_char->getWidth()&&item_P.x>=char_P.x && item_P.y >=char_P.y &&item_P.y<=char_P.y+g_char->getHeight())
		{
			this->removeChild((*g_item_iterator));
			g_item_iterator=g_itemlist.erase(g_item_iterator);
			
		}
			
	}
		
	//mob collision check
	CCPoint mob_P;

	for(g_mob_iterator = g_moblist.begin(); g_mob_iterator != g_moblist.end(); g_mob_iterator++)
	{
		temp = *(g_mob_iterator);
		mob_P=temp->getPosition();
		
		if(mob_P.x<-20)
		{
			this->removeChild((*g_mob_iterator)); 
			g_mob_iterator=g_moblist.erase(g_mob_iterator);
		}
		
		if(char_P.x >mob_P.x)
		{
			g_char->setJump(8);
		}


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
	
	if(maptemp->getPositionX() <0&&maptemp->getPositionX()>-11)
	{
		CCSprite* item[5];

		for(int i =0;i<5;i++)
		{
			item[i] = CCSprite::create("item.png");
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
			item[i] = CCSprite::create("item.png");
			item[i]->setAnchorPoint(ccp(0,0));
			item[i]->setPosition(ccp(500+100*i+1280,220));
			this->addChild(item[i]);

			g_itemlist.push_back(item[i]);

		}
	}
		
		
}


void GameScene::itemScrolling()
{
	
	CCPoint item_P;
	CCSprite* temp;
	for(g_item_iterator = g_itemlist.begin(); g_item_iterator != g_itemlist.end(); g_item_iterator++)
	{
		temp = (*g_item_iterator);
		item_P=temp->getPosition();
		temp->setPosition(ccp(item_P.x-game_speed,item_P.y));
	}

}



void GameScene::createmob()
{
	
	CCSprite* maptemp;

	maptemp = g_map->getMap(1);

	if(maptemp->getPositionX() <0&&maptemp->getPositionX()>-11)
	{
		CCSprite* mob;

		mob = CCSprite::create("mob.png");
		mob->setAnchorPoint(ccp(0,0));
		mob->setPosition(ccp(1000,180));
		this->addChild(mob);
		
		g_moblist.push_back(mob);

	}

	
	maptemp = g_map->getMap(2);
	
	if(maptemp->getPositionX() <=1270&&maptemp->getPositionX()>-4+1270)
	{
		
		CCSprite* mob;

		mob = CCSprite::create("mob.png");
		mob->setAnchorPoint(ccp(0,0));
		mob->setPosition(ccp(1000+1280,180));
		this->addChild(mob);
		
		g_moblist.push_back(mob);


	}

}

void GameScene::mobScrolling()
{
	
	CCPoint mob_P;
	CCSprite* temp;
	for(g_mob_iterator = g_moblist.begin(); g_mob_iterator != g_moblist.end(); g_mob_iterator++)
	{
		temp = (*g_mob_iterator);
		mob_P=temp->getPosition();
		temp->setPosition(ccp(mob_P.x-game_speed,mob_P.y));
	}

}

void GameScene::mapInit()
{

	/*
	floor_test1= CCTMXTiledMap::create("floor_test2.tmx");
	floor_test1->setAnchorPoint(ccp(0,0));
	floor_test1->setPosition(ccp(0,0));

	this->addChild(floor_test1,1);



	floor_test2 = CCTMXTiledMap::create("floor_test.tmx");
	floor_test2->setAnchorPoint(ccp(0,0));
	floor_test2->setPosition(ccp(1280,0));

	this->addChild(floor_test2,1);

	CCTMXLayer* layer1 = floor_test2->layerNamed("floor");
	CCSize size1 = layer1->getContentSize();

		

	for( unsigned int y=0; y <size1.height/20; y++ )
	{
			
		for( unsigned int x=0; x <size1.width/20; x++ ) 
		{
							
			
			unsigned int gid = layer1->tileGIDAt(ccp(x,y));
							
							
			if( gid != 0 ) 
			{
				g_floor.push_back(ccp(64+x,size1.height/20-y));
			}
		}
	}        
	*/
	
	floor_test1= CCTMXTiledMap::create("tilemap.tmx");
	floor_test1->setAnchorPoint(ccp(0,0));
	floor_test1->setPosition(ccp(0,0));

	this->addChild(floor_test1,1);

	CCTMXLayer* layer1 = floor_test1->layerNamed("floor");
	CCSize size1 = layer1->getContentSize();

		

	for( unsigned int y=0; y <size1.height/20; y++ )
	{
			
		for( unsigned int x=0; x <size1.width/20; x++ ) 
		{
							
			
			unsigned int gid = layer1->tileGIDAt(ccp(x,y));
							
							
			if( gid !=0 ) 
			{
				g_floor.push_back(ccp(x,size1.height/20-y));
			}
		}
	}        

	
	CCTMXLayer* layer2 = floor_test1->layerNamed("item");
	CCSize size2 = layer2->getContentSize();

		

	for( unsigned int y=0; y <size1.height/20; y++ )
	{
			
		for( unsigned int x=0; x <size1.width/20; x++ ) 
		{
							
			
			unsigned int gid = layer2->tileGIDAt(ccp(x,y));
							
							
			if( gid != 0) 
			{
				CCSprite* tempitem = CCSprite::create("130707_coin2.png");
				tempitem->setAnchorPoint(ccp(0,0));
				tempitem->setPosition(ccp(x*20,(size1.height/20-y)*20));
				this->addChild(tempitem,2);
				g_itemlist.push_back(tempitem);
			}
		}
	}        

	CCTMXLayer* layer3 = floor_test1->layerNamed("monster");
	CCSize size3 = layer3->getContentSize();

		
	
	for( unsigned int y=0; y <size3.height/20; y++ )
	{
			
		for( unsigned int x=0; x <size3.width/20; x++ ) 
		{
							
			
			unsigned int gid = layer3->tileGIDAt(ccp(x,y));
							
							
			if( gid !=0 ) 
			{
				CCSprite* tempmob = CCSprite::create("object1_edit.png");
				tempmob->setAnchorPoint(ccp(0,0));
				tempmob->setPosition(ccp(x*20,(size3.height/20-y)*20));
				this->addChild(tempmob,2);
				g_moblist.push_back(tempmob);
			}
		}
	}        

	

	floor_test2 = CCTMXTiledMap::create("floor_test2.tmx");
	floor_test2->setAnchorPoint(ccp(0,0));
	floor_test2->setPosition(ccp(6390,0));

	this->addChild(floor_test2,1);


	

}

void GameScene::mapScrolling()
{
	CCPoint map1_P;
	CCPoint map2_P;

	

	map1_P = floor_test1->getPosition();
	map2_P = floor_test2->getPosition();
	
	floor_test1->setPositionX(map1_P.x-game_speed);
	floor_test2->setPositionX(map2_P.x-game_speed);
	if(map1_P.x<= -6400)
	{
		
		CCTMXTiledMap* temp;

		temp = floor_test1;
		floor_test1 = floor_test2;
		floor_test2 = temp;
		
		floor_test2->setPositionX(1270);
	}
}


void GameScene::floorcheck()
{
	CCPoint char_P = m_character->getPosition();
	
	GridY = char_P.y/20;

	scroll_count += game_speed;

	if(scroll_count >=20)
	{
		GridX++;
		scroll_count=0;
	}

	CCPoint temp;

	CCLog("%d %d",GridX,GridY);

	for(g_floor_iterator = g_floor.begin(); g_floor_iterator != g_floor.end(); g_floor_iterator++)
	{

		temp = *(g_floor_iterator);
		
		if(GridX == temp.x && GridY ==temp.y)
		{
			g_char->setfloorcheck(1);

		}

		
		
	}
	

}


void GameScene::charInit()
{

	m_character = CCSprite::create("main character_edit.png",CCRect(140,0,140,160));
	this -> addChild(m_character,2);

	m_character->setAnchorPoint(ccp(0,0));
	m_character->setPosition(ccp(100,200));

	g_char = new Character(m_character);
				
	CCPoint char_P = m_character->getPosition();
	
	GridX = char_P.x/20+2;

}