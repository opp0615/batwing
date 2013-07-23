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
	collisionCheck();
	itemScrolling();
	mobScrolling();
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
	CCPoint mob2_P;
	int char_width;
	int char_height;

	int mob_width = 120;
	int mob_height = 140;

	char_temp = g_char->getChar();
	char_P = char_temp->getPosition();

	char_width = g_char->getWidth();
	char_height =g_char->getHeight();
	

	//item collision check
	
	

	for(g_item_iterator = g_itemlist.begin(); g_item_iterator != g_itemlist.end(); )
	{
		bool bDeleted = false;
		temp = *(g_item_iterator);
			
		item_P=temp->getPosition();
		
		if(item_P.x<-200)
		{
			this->removeChild((*g_item_iterator)); 
			g_item_iterator=g_itemlist.erase(g_item_iterator++);
			bDeleted = true;
		}		

		if(item_P.x <= char_P.x+char_width && item_P.x>=char_P.x && item_P.y >=char_P.y &&item_P.y<=char_P.y+char_height)
		{
			this->removeChild((*g_item_iterator));
			g_item_iterator=g_itemlist.erase(g_item_iterator++);
			bDeleted = true;
		}
			
		if (!bDeleted)
		{
			g_item_iterator++;
		}
	
	}
	
	//mob collision check
	CCPoint mob_P;
	
	
	for(g_mob_iterator = g_moblist.begin(); g_mob_iterator != g_moblist.end(); )
	{
		bool bDeleted = false;

		temp = *(g_mob_iterator);
		mob_P=temp->getPosition();
		
		if(mob_P.x<-200)
		{
			this->removeChild((*g_mob_iterator)); 
			g_mob_iterator=g_moblist.erase(g_mob_iterator++);
			
			bDeleted = true;
		}
		
		if(g_char->getCharSpeed() <0 && char_P.x+char_width >mob_P.x && char_P.x + char_width < mob_P.x + 120 &&char_P.y <mob_P.y+140 && char_P.y > mob_P.y +100)
		{
			this->removeChild((*g_mob_iterator)); 
			g_mob_iterator=g_moblist.erase(g_mob_iterator++);
			g_char->setJump(10);
			CCLog("!!!Collision");
			bDeleted = true;
		}
	

		if(!bDeleted )
		{
			g_mob_iterator++;
		}
	}
	
	//mob2 collision

	for(g_mob_iterator2 = g_moblist2.begin(); g_mob_iterator2 != g_moblist2.end(); )
	{
		bool bDeleted = false;

		temp = *(g_mob_iterator2);
		mob2_P=temp->getPosition();
		
		if(mob2_P.x<-200)
		{
			this->removeChild((*g_mob_iterator2)); 
			g_mob_iterator2=g_moblist2.erase(g_mob_iterator2++);
			
			bDeleted = true;
		}
		
		if(g_char->getCharSpeed() <0 && char_P.x+char_width >mob2_P.x && char_P.x + char_width < mob2_P.x +120 &&char_P.y <mob2_P.y+225 && char_P.y >mob2_P.y + 180)
		{
			this->removeChild((*g_mob_iterator2)); 
			g_mob_iterator2=g_moblist2.erase(g_mob_iterator2++);
			g_char->setJump(10);
			CCLog("!!!Collision");
			bDeleted = true;
		}
	

		if(!bDeleted )
		{
			g_mob_iterator2++;
		}
	}
	
	
	
}
void GameScene::ccTouchesBegan(CCSet* touches,CCEvent* evnet)
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	g_char->setClick(g_char->getClick());
	g_char->setJump(10);
}


void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
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

	for(g_mob_iterator2 = g_moblist2.begin(); g_mob_iterator2 != g_moblist2.end(); g_mob_iterator2++)
	{
		temp = (*g_mob_iterator2);
		mob_P=temp->getPosition();
		temp->setPosition(ccp(mob_P.x-game_speed,mob_P.y));
	}

		
	for(g_object_iterator = g_object.begin(); g_object_iterator != g_object.end(); g_object_iterator++)
	{
		temp = (*g_object_iterator);
		mob_P=temp->getPosition();
		temp->setPosition(ccp(mob_P.x-game_speed,mob_P.y));
	}

}

void GameScene::mapInit()
{

	
	floor_test1= CCTMXTiledMap::create("prototype.tmx");
	floor_test1->setAnchorPoint(ccp(0,0));
	floor_test1->setPosition(ccp(0,0));

	this->addChild(floor_test1,1);


	map1create();

	//map2 Init



	floor_test2 = CCTMXTiledMap::create("prototype.tmx");
	floor_test2->setAnchorPoint(ccp(0,0));
	floor_test2->setPosition(ccp(7490,0));

	this->addChild(floor_test2,1);

	map2create();

}

void GameScene::mapScrolling()
{
	CCPoint map1_P;
	CCPoint map2_P;

	

	map1_P = floor_test1->getPosition();
	map2_P = floor_test2->getPosition();
	
	floor_test1->setPositionX(map1_P.x-game_speed);
	floor_test2->setPositionX(map2_P.x-game_speed);
	if(map1_P.x<= -7490)
	{
		
		CCTMXTiledMap* temp;

		temp = floor_test1;
		floor_test1 = floor_test2;
		floor_test2 = temp;
		
		floor_test2->setPositionX(7490);

		//map1create();
		//map2create();
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

	CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("main character_edit.png");
    
    // manually add frames to the frame cache
    CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*0,0,140,160));
    CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*1,0,140,160));
       
    
    //
    // Animation using Sprite BatchNode
    //

	m_character = CCSprite::createWithSpriteFrame(frame0);
	m_character->setAnchorPoint(ccp(0,0));
	m_character->setPosition(ccp(100,100));

    this->addChild(m_character);
            
    CCArray* animFrames = CCArray::createWithCapacity(6);
    animFrames->addObject(frame0);
    animFrames->addObject(frame1);
   
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
    CCAnimate *animate = CCAnimate::create(animation);
    CCActionInterval* seq = CCSequence::create( animate,
                       NULL);
    
	

    m_character->runAction(CCRepeatForever::create( seq ) );


	/*
	m_character = CCSprite::create("main character_edit.png",CCRect(140,0,140,160));
	this -> addChild(m_character,2);

	m_character->setAnchorPoint(ccp(0,0));
	m_character->setPosition(ccp(100,200));
	*/
	g_char = new Character(m_character);
				
	CCPoint char_P = m_character->getPosition();
	
	GridX = char_P.x/20+2;


}


void GameScene::map1create()
{
		
	
	CCTMXLayer* layer1 = floor_test1->layerNamed("floor");
	CCSize size1 = layer1->getContentSize();


	for( unsigned int x=0; x <size1.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size1.height/20; y++ ) 
		{
							
			
			unsigned int gid = layer1->tileGIDAt(ccp(x,y));
			
							
			if( gid !=0 ) 
			{
				g_floor.push_back(ccp(x,size1.height/20-y));
			}
		}
	}        

	
	CCTMXLayer* layer2 = floor_test1->layerNamed("coin");
	CCSize size2 = layer2->getContentSize();

		

	for( unsigned int x=0; x <size2.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size2.height/20; y++ ) 
		{
							
			
			unsigned int gid = layer2->tileGIDAt(ccp(x,y));
							
							
			if( gid != 0) 
			{
				CCSprite* tempitem = CCSprite::create("130707_coin3.png");
				tempitem->setAnchorPoint(ccp(0,0));
				tempitem->setPosition(ccp(x*20,(size2.height/20-y)*20));
				this->addChild(tempitem,2);
				g_itemlist.push_back(tempitem);
			}
		}
	}        

	CCTMXLayer* layer3 = floor_test1->layerNamed("mob1");
	CCSize size3 = layer3->getContentSize();

		
	
	for( unsigned int x=0; x <size3.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size3.height/20; y++ ) 
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

	CCTMXLayer* layer4 = floor_test1->layerNamed("mob2");
	CCSize size4 = layer4->getContentSize();

		
	
	for( unsigned int x=0; x <size4.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size4.height/20; y++ ) 
		{
							
			
			unsigned int gid = layer4->tileGIDAt(ccp(x,y));
							
							
			if( gid !=0 ) 
			{
				CCSprite* tempmob = CCSprite::create("object2_edit.png");
				tempmob->setAnchorPoint(ccp(0,0));
				tempmob->setPosition(ccp(x*20,(size3.height/20-y)*20));
				this->addChild(tempmob,2);
				g_moblist2.push_back(tempmob);
			}
		}
	}     

	CCTMXLayer* layer5 = floor_test1->layerNamed("object");
	CCSize size5 = layer5->getContentSize();

		
	
	for( unsigned int x=0; x <size5.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size5.height/20; y++ ) 
		{
							
			
			unsigned int gid = layer5->tileGIDAt(ccp(x,y));
							
							
			if( gid !=0 ) 
			{
				CCSprite* tempmob = CCSprite::create("130710_4.png");
				tempmob->setAnchorPoint(ccp(0,0));
				tempmob->setPosition(ccp(x*20,(size3.height/20-y)*20));
				this->addChild(tempmob,2);
				g_object.push_back(tempmob);
			}
		}
	}        

}

void GameScene::map2create()
{
	
	CCTMXLayer* layer6 = floor_test2->layerNamed("floor");
	CCSize size6 = layer6->getContentSize();

		

	for( unsigned int x=0; x <size6.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size6.height/20; y++ ) 
		{
							
			
			unsigned int gid = layer6->tileGIDAt(ccp(x,y));
							
							
			if( gid !=0 ) 
			{
				g_floor.push_back(ccp(x+7490/20,size6.height/20-y));
			}
		}
	}        

	
	CCTMXLayer* layer7 = floor_test2->layerNamed("coin");
	CCSize size7= layer7->getContentSize();

		

	for( unsigned int x=0; x <size7.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size7.height/20; y++ ) 
		{
							
			
			unsigned int gid = layer7->tileGIDAt(ccp(x,y));
							
							
			if( gid != 0) 
			{
				CCSprite* tempitem = CCSprite::create("130707_coin3.png");
				tempitem->setAnchorPoint(ccp(0,0));
				tempitem->setPosition(ccp(x*20+7490,(size7.height/20-y)*20));
				this->addChild(tempitem,2);
				g_itemlist.push_back(tempitem);
			}
		}
	}        

	CCTMXLayer* layer8 = floor_test2->layerNamed("mob1");
	CCSize size8 = layer8->getContentSize();

		
	
	for( unsigned int x=0; x <size8.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size8.height/20; y++ ) 
		{
							
			
			unsigned int gid = layer8->tileGIDAt(ccp(x,y));
							
							
			if( gid !=0 ) 
			{
				CCSprite* tempmob = CCSprite::create("object1_edit.png");
				tempmob->setAnchorPoint(ccp(0,0));
				tempmob->setPosition(ccp(x*20+7490,(size8.height/20-y)*20));
				this->addChild(tempmob,2);
				g_moblist.push_back(tempmob);
			}
		}
	}        

	CCTMXLayer* layer9 = floor_test2->layerNamed("mob2");
	CCSize size9 = layer9->getContentSize();

		
	
	for( unsigned int x=0; x <size9.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size9.height/20; y++ ) 
		{
							
			
			unsigned int gid = layer9->tileGIDAt(ccp(x,y));
							
							
			if( gid !=0 ) 
			{
				CCSprite* tempmob = CCSprite::create("object2_edit.png");
				tempmob->setAnchorPoint(ccp(0,0));
				tempmob->setPosition(ccp(x*20+7490,(size9.height/20-y)*20));
				this->addChild(tempmob,2);
				g_moblist2.push_back(tempmob);
			}
		}
	}     

	CCTMXLayer* layer10 = floor_test2->layerNamed("object");
	CCSize size10 = layer10->getContentSize();

		
	
	for( unsigned int x=0; x <size10.width/20; x++ )
	{
			
		for( unsigned int y=0; y <size10.height/20; y++ ) 
		{
							
			
			unsigned int gid = layer10->tileGIDAt(ccp(x,y));
							
							
			if( gid !=0 ) 
			{
				CCSprite* tempmob = CCSprite::create("130710_4.png");
				tempmob->setAnchorPoint(ccp(0,0));
				tempmob->setPosition(ccp(x*20+7490,(size10.height/20-y)*20));
				this->addChild(tempmob,2);
				g_object.push_back(tempmob);
			}
		}
	}        



}