#include "GameScene.h"

#define character_width 140
#define character_height 160
#define coin_width 40
#define coin_height 40
#define mob1_width 80
#define mob1_height 142
#define mob2_width 94
#define mob2_height 226
#define object_width 100
#define object_height 110
#define pause_identity 3
#define boss_width 200
#define boss_height 220

#define tag_pause 77

#define tag_pauseScene 88
#define tag_continue 89
#define tag_goToMenu 90
#define tag_soundControl 91
#define tag_bgmControl 92
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


		scoreInit();
		g_gameSuccess =false;
		g_pauseClick=false;
		g_gameOverCheck = false;
		pauseCheckAni=0;

		g_checktime = 0;
		g_temptime = 0;
		g_loadtime =0;
		g_checkmagnetic;

		CCSprite* pause = CCSprite::create("130827_Pause.png");
		pause->setAnchorPoint(ccp(0,0));
		pause->setPosition(ccp(1160,620));
		this->addChild(pause,2,tag_pause);

		g_virtual_char.setPoint(100,120);

		/*
		CCSprite* score_bakground = CCSprite::create("130827_score2.png");
		score_bakground->setAnchorPoint(ccp(0,0));
		score_bakground->setPosition(ccp(50,600));
		this->addChild(score_bakground,2);
		*/

		CCSprite* positionbar = CCSprite::create("131104_ingamebar_resized(496x15).png");
		positionbar->setAnchorPoint(ccp(0,0));
		positionbar->setPosition(ccp(440,615));
		this->addChild(positionbar,2);

		CCSprite* goalin = CCSprite::create("130830_Object2.png");
		goalin->setAnchorPoint(ccp(0,0));
		goalin->setPosition(ccp(931,630));
		this->addChild(goalin,1);

		nowpositionpoint = CCSprite::create("130830_Object1_resized.png");
		nowpositionpoint->setAnchorPoint(ccp(0,0));
		nowpositionpoint->setPosition(ccp(435,630));
		this->addChild(nowpositionpoint,2);

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

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
			"pandora.wav",true);
	}
	return true;
}

void GameScene::update(float dt)
{
	if(checkTime() >= 10)
	{
		g_checktime += 0.1;
		g_temptime = 0;
	}
	nowpositionpoint->setPositionX(nowpositionpoint->getPositionX()+0.1);
	g_map->Scrolling();
	g_char->Accel();
	g_char->animationControl();
	itemScrolling();
	mobScrolling();
	mapScrolling();
	floorcheck();
	scoreUpdate();
	collisionCheck();

}

void GameScene::collisionCheck()
{


	CCPoint char_P=m_character->getPosition();


	CCSprite* char_temp;
	CCSprite* temp;
	CCPoint char_p;
	CCPoint item_P;
	CCPoint mob2_P;
	CCPoint object_P;
	int char_width;
	int char_height;

	int mob_width = 120;
	int mob_height = 140;

	char_temp = g_char->getChar();
	char_P = char_temp->getPosition();

	char_width = g_char->getWidth();
	char_height =g_char->getHeight();


	//item collision check

	

	for(g_coin_bronze_iterator = g_coin_bronze.begin(); g_coin_bronze_iterator != g_coin_bronze.end(); )
	{
		bool bDeleted = false;
		temp = *(g_coin_bronze_iterator);

		item_P=temp->getPosition();

		if(item_P.x<-200)
		{
			this->removeChild((*g_coin_bronze_iterator)); 
			g_coin_bronze_iterator=g_coin_bronze.erase(g_coin_bronze_iterator++);
			bDeleted = true;
		}		


		if(item_P.x  < char_P.x+character_width && item_P.x + coin_width > char_P.x && item_P.y + coin_height >char_P.y &&item_P.y<char_P.y+character_height)
		{
			g_score_item++;
			this->removeChild((*g_coin_bronze_iterator));
			g_coin_bronze_iterator=g_coin_bronze.erase(g_coin_bronze_iterator++);
			bDeleted = true;
		}

		if (!bDeleted)
		{
			g_coin_bronze_iterator++;
		}

	}


	for(g_coin_silver_iterator = g_coin_silver.begin(); g_coin_silver_iterator != g_coin_silver.end(); )
	{
		bool bDeleted = false;
		temp = *(g_coin_silver_iterator);

		item_P=temp->getPosition();

		if(item_P.x<-200)
		{
			this->removeChild((*g_coin_silver_iterator)); 
			g_coin_silver_iterator=g_coin_silver.erase(g_coin_silver_iterator++);
			bDeleted = true;
		}		


		if(item_P.x  < char_P.x+character_width && item_P.x + coin_width > char_P.x && item_P.y + coin_height >char_P.y &&item_P.y<char_P.y+character_height)
		{
			g_score_item++;
			this->removeChild((*g_coin_silver_iterator));
			g_coin_silver_iterator=g_coin_silver.erase(g_coin_silver_iterator++);
			bDeleted = true;
		}

		if (!bDeleted)
		{
			g_coin_silver_iterator++;
		}

	}



	for(g_coin_gold_iterator = g_coin_gold.begin(); g_coin_gold_iterator != g_coin_gold.end(); )
	{
		bool bDeleted = false;
		temp = *(g_coin_gold_iterator);

		item_P=temp->getPosition();

		if(item_P.x<-200)
		{
			this->removeChild((*g_coin_gold_iterator)); 
			g_coin_gold_iterator=g_coin_gold.erase(g_coin_gold_iterator++);
			bDeleted = true;
		}		


		if(item_P.x  < char_P.x+character_width && item_P.x + coin_width > char_P.x && item_P.y + coin_height >char_P.y &&item_P.y<char_P.y+character_height)
		{
			g_score_item++;
			this->removeChild((*g_coin_gold_iterator));
			g_coin_gold_iterator=g_coin_gold.erase(g_coin_gold_iterator++);
			bDeleted = true;
		}

		if (!bDeleted)
		{
			g_coin_gold_iterator++;
		}

	}


	//mob collision check
	CCPoint mob_P;

	mob_P = g_boss->getPosition();

	if(mob_P.x  < char_P.x+character_width && mob_P.x + boss_width > char_P.x && mob_P.y + boss_height >char_P.y &&mob_P.y<char_P.y+character_height)
	{
		this->removeChild(g_boss);
		endStage();
	}

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

		if( char_P.x+character_width - 30 >mob_P.x && char_P.x + 30< mob_P.x + mob1_width &&char_P.y  + 30<mob_P.y+mob1_height && char_P.y + character_height -30 > mob_P.y -30)
		{
			if(g_char->getCharSpeed() < 0 && char_P.x+character_width-30 >mob_P.x && char_P.x+30< mob_P.x + mob1_width &&char_P.y +30<mob_P.y+mob1_height && char_P.y + character_height-30 > mob_P.y + mob1_height -30)
			{
				g_char->mobjump();
				g_score_mob1++;
				this->removeChild((*g_mob_iterator)); 
				g_mob_iterator=g_moblist.erase(g_mob_iterator++);
				CCLog("!!!MobCollision!!!");
				bDeleted = true;
			}

			if( char_P.x+character_width- 30  >mob_P.x && char_P.x+ 30< mob_P.x + mob1_width &&char_P.y+ 30 <mob_P.y+mob1_height -30 && char_P.y + character_height-30  > mob_P.y -10)
			{
				
				gameOver();

				return ;
			}
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


		if(char_P.x+character_width -30 >mob2_P.x && char_P.x+30 < mob2_P.x + mob2_width &&char_P.y +30 <mob2_P.y+mob2_height && char_P.y + character_height-30 > mob2_P.y -30)
		{
			if(g_char->getCharSpeed() <0 && char_P.x+character_width -30 >mob2_P.x && char_P.x+30< mob2_P.x + mob2_width &&char_P.y +30<mob2_P.y+mob2_height && char_P.y + character_height-30 > mob2_P.y + mob2_height -30)
			{
				g_char->mobjump();
				g_score_mob2++;
				this->removeChild((*g_mob_iterator2));
				g_mob_iterator2=g_moblist2.erase(g_mob_iterator2++);

				bDeleted = true;
			}

			if (char_P.x+character_width-30 >mob2_P.x && char_P.x+30< mob2_P.x + mob2_width &&char_P.y+30 <mob2_P.y+mob2_height-30 && char_P.y + character_height-30 > mob2_P.y -10)
			{
				g_char->runDeadAnimation();

				gameOver();


				return ;
			}
		}

		if(!bDeleted )
		{
			g_mob_iterator2++;
		}
	}
	//object collision check
	for(g_object_iterator = g_object.begin(); g_object_iterator != g_object.end(); )
	{
		bool bDeleted = false;
		temp = *(g_object_iterator);
		object_P = temp -> getPosition();

		if(char_P.x+character_width -30 >object_P.x +20 && char_P.x + 30 < object_P.x + object_width -20 &&char_P.y +30 <object_P.y+object_height -20 && char_P.y + character_height -30 > object_P.y -30)
		{
			g_char->runDeadAnimation();

			gameOver();


			return;
		}

		if(!bDeleted )
		{
			g_object_iterator++;
		}
	}

	//land checked

	if( char_P.y >=100 && char_P.y<= 130 && g_char->getClick() !=0 && g_char->getCharSpeed()<0)
	{
		m_character->cleanup();
		g_char->setCheckAniamtion(0);
		m_character->setPositionY(120);
	}


}

void GameScene::ccTouchesBegan(CCSet* touches,CCEvent* evnet)
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	if(g_gameOverCheck == false && g_gameSuccess ==false)
	{
		if(g_pauseClick == false)//pause
		{
			if( 1160<=location.x && location.x<=1160 + 70 && 620<=location.y && location.y<=620+70)
			{
				CCSprite* getter;
				getter = (CCSprite*)this->getChildByTag(tag_pause);

				CCActionInterval* buttonPop = CCScaleTo::create(0.1,1.2,1.2);

				getter->runAction(buttonPop);


				pause();

				pauseCheckAni = g_char->getCheckAnimation();
				CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
				this->pauseSchedulerAndActions();
				m_character->pauseSchedulerAndActions();
				g_pauseClick = true;
			}

			else //jump
			{
				g_char->setClick(g_char->getClick());
				g_char->setJump(15);
			}

		}

		//pause control


		else //resume
		{
			if(895<=location.x && location.x<=895 + 250 && 411<=location.y && location.y<=411+75)
			{
				for(int i =88;i<93;i++)
				{
					this->removeChildByTag(i);
				}

				CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
				this->resumeSchedulerAndActions();
				m_character->resumeSchedulerAndActions();
				g_char->setCheckAniamtion(pauseCheckAni);
				g_pauseClick = false;
			}

			else if(895<=location.x && location.x<=895 + 250 && 296<=location.y && location.y<=296+75)
			{
				CCScene *pScene = MainmenuScene::scene();
				CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
				CCDirector::sharedDirector()->replaceScene(pTran);


				g_pauseClick = false;
			}

			else if(895<=location.x && location.x<=895 + 250 && 181<=location.y && location.y<=181+75)
			{

			}

			else if(895<=location.x && location.x<=895 + 250 && 65<=location.y && location.y<=65+75)
			{

			}
		}
	}


	else if(g_gameOverCheck ==true)//dead(Game Over)
	{

		if( 895<=location.x && location.x<=895 + 250 && 228<=location.y && location.y<=228+75)
		{

			CCScene *pScene = GameScene::scene();
			CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
			CCDirector::sharedDirector()->replaceScene(pTran);
		}

		else if( 895<=location.x && location.x<=895 + 250 && 109<=location.y && location.y<=109+75)
		{
			CCScene *pScene = MainmenuScene::scene();
			CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
			CCDirector::sharedDirector()->replaceScene(pTran);
		}
	}

	else if(g_gameSuccess ==true)
	{
		
		if( 895<=location.x && location.x<=895 + 250 && 109<=location.y && location.y<=109+75)
		{
			CCScene *pScene = MainmenuScene::scene();
			CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
			CCDirector::sharedDirector()->replaceScene(pTran);
		}

	}


}




void GameScene::itemScrolling()
{

	CCPoint item_P;
	CCSprite* temp;

	//coin scrolling
	for(g_coin_bronze_iterator = g_coin_bronze.begin(); g_coin_bronze_iterator != g_coin_bronze.end(); g_coin_bronze_iterator++)
	{
		temp = (*g_coin_bronze_iterator);
		item_P=temp->getPosition();
		temp->setPosition(ccp(item_P.x-game_speed,item_P.y));
	}


	for(g_coin_silver_iterator = g_coin_silver.begin(); g_coin_silver_iterator != g_coin_silver.end(); g_coin_silver_iterator++)
	{
		temp = (*g_coin_silver_iterator);
		item_P=temp->getPosition();
		temp->setPosition(ccp(item_P.x-game_speed,item_P.y));
	}

	
	for(g_coin_gold_iterator = g_coin_gold.begin(); g_coin_gold_iterator != g_coin_gold.end(); g_coin_gold_iterator++)
	{
		temp = (*g_coin_gold_iterator);
		item_P=temp->getPosition();
		temp->setPosition(ccp(item_P.x-game_speed,item_P.y));
	}

	//item scrolling
	for(g_huge_item_iterator = g_huge_item.begin(); g_huge_item_iterator != g_huge_item.end(); g_huge_item_iterator++)
	{
		temp = (*g_huge_item_iterator);
		item_P=temp->getPosition();
		temp->setPosition(ccp(item_P.x-game_speed,item_P.y));
	}

	for(g_coin_item_iterator = g_coin_item.begin(); g_coin_item_iterator != g_coin_item.end(); g_coin_item_iterator++)
	{
		temp = (*g_coin_item_iterator);
		item_P=temp->getPosition();
		temp->setPosition(ccp(item_P.x-game_speed,item_P.y));
	}

	for(g_run_item_iterator = g_run_item.begin(); g_run_item_iterator != g_run_item.end(); g_run_item_iterator++)
	{
		temp = (*g_run_item_iterator);
		item_P=temp->getPosition();
		temp->setPosition(ccp(item_P.x-game_speed,item_P.y));
	}

	for(g_magnet_item_iterator = g_magnet_item.begin(); g_magnet_item_iterator != g_magnet_item.end(); g_magnet_item_iterator++)
	{
		temp = (*g_magnet_item_iterator);
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
	mob_P = g_boss->getPosition();
	g_boss->setPosition(ccp(mob_P.x-game_speed,mob_P.y));

}

void GameScene::mapInit()
{
	//Tile limit 16400
	/*
	map_level[0]= CCTMXTiledMap::create("stage1level1.tmx");

	map_level[0]->setAnchorPoint(ccp(0,0));
	map_level[0]->setPosition(ccp(0,0));

	this->addChild(map_level[0],2);
	mapdataload(map_level[0],0);
	*/

	map_level[0] = CCTMXTiledMap::create("stage1_level1.tmx");
	map_level[1] = CCTMXTiledMap::create("stage1_level2.tmx");
	map_level[2] = CCTMXTiledMap::create("stage1_level3.tmx");
	map_level[3] = CCTMXTiledMap::create("stage1_level4.tmx");

	for(int i=0;i<4;i++)
	{
		map_level[i]->setAnchorPoint(ccp(0,0));
		map_level[i]->setPosition(ccp(7500*i,0));
		mapdataload(map_level[i],i);
		this->addChild(map_level[i],4);
	}

	CCLog("");
}

void GameScene::mapScrolling()
{


	CCPoint map_P;

	for(int i =0;i<4;i++)
	{
		map_P = map_level[i]->getPosition();
		map_level[i]->setPositionX(map_P.x-game_speed);
		/*
		if(map_P.x < -8000)
		{
		this->removeChild(map_level[i]);
		}
		*/
	}

}


void GameScene::floorcheck()
{
	CCPoint temp_char = m_character->getPosition();

	CCPoint temp;
	g_virtual_char.setPoint(g_virtual_char.x+ game_speed,temp_char.y);
	CCLog("%f %f",g_virtual_char.x,g_virtual_char.y ); 
	for(g_floor_iterator = g_floor.begin(); g_floor_iterator != g_floor.end(); g_floor_iterator++)
	{

		temp = *(g_floor_iterator);

		if(temp.x  < g_virtual_char.x+character_width && temp.x + coin_width > g_virtual_char.x && temp.y + coin_height >g_virtual_char.y &&temp.y<g_virtual_char.y+character_height)
		{
			g_char->setfloorcheck(1);

		}

		temp.setPoint(temp.x -game_speed ,temp.y) ;

	}



}


void GameScene::charInit()
{

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("main character.png");



	// manually add frames to the frame cache
	CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*0,0,140,160));
	CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*1,0,140,160));
	CCSpriteFrame *frame2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*2,0,140,160));
	CCSpriteFrame *frame3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*3,0,140,160));
	CCSpriteFrame *frame4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*4,0,140,160));
	CCSpriteFrame *frame5 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*5,0,140,160));
	CCSpriteFrame *frame6 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*6,0,140,160));
	CCSpriteFrame *frame7 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*7,0,140,160));
	CCSpriteFrame *frame8 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*8,0,140,160));
	CCSpriteFrame *frame9 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*9,0,140,160));
	CCSpriteFrame *frame10 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*10,0,140,160));


	m_character = CCSprite::createWithSpriteFrame(frame0);

	m_character->setAnchorPoint(ccp(0,0));
	m_character->setPosition(ccp(100,120));

	this->addChild(m_character,3);



	CCArray* animFrames0 = CCArray::createWithCapacity(6);
	animFrames0->addObject(frame0);
	animFrames0->addObject(frame1);

	CCArray* animFrames1 = CCArray::createWithCapacity(6);
	animFrames1->addObject(frame2);

	CCArray* animFrames2 = CCArray::createWithCapacity(6);
	animFrames2->addObject(frame3);
	animFrames2->addObject(frame4);
	animFrames2->addObject(frame5);
	animFrames2->addObject(frame6);
	animFrames2->addObject(frame7);
	animFrames2->addObject(frame8);



	CCArray* animFrames3 = CCArray::createWithCapacity(2);
	animFrames3 ->addObject(frame9);
	animFrames3 ->addObject(frame10);

	CCAnimation * animation0 = CCAnimation::createWithSpriteFrames(animFrames0, 0.1f);
	CCAnimate *animate0 = CCAnimate::create(animation0);
	CCActionInterval* seq0 = CCSequence::create( animate0,NULL);

	CCAnimation *  animation1 = CCAnimation::createWithSpriteFrames(animFrames1, 0.1f);
	CCAnimate *animate1 = CCAnimate::create(animation1);
	CCActionInterval* seq1 = CCSequence::create( animate1,NULL);

	CCAnimation * animation2 = CCAnimation::createWithSpriteFrames(animFrames2, 0.1f);
	CCAnimate *animate2 = CCAnimate::create(animation2);
	CCActionInterval* seq2 = CCSequence::create( animate2,NULL);

	CCAnimation* animation3 = CCAnimation::createWithSpriteFrames(animFrames3,0.1f);
	CCAnimate *animate3 = CCAnimate::create(animation3);

	runact   = CCRepeatForever::create(seq0);
	jump1act = CCRepeatForever::create(seq1);
	jump2act = CCRepeatForever::create(seq2);
	deadact = CCRepeat::create(animate3,1);
	//
	// Animation using Sprite BatchNode
	//
	//m_character->runAction(runact);

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

void GameScene::mapdataload(CCTMXTiledMap* map,int i)
{


	CCTMXObjectGroup * group = map->objectGroupNamed("coin_bronze");

	if(group !=NULL)
	{
		CCArray* objects = group->getObjects();

		CCDictionary* dict = NULL;
		CCObject* pObj = NULL;

		CCARRAY_FOREACH(objects,pObj)
		{
			dict = (CCDictionary*)pObj;

			CCSprite* tempitem = CCSprite::create("130710_coin_bronze.png");
			tempitem->setAnchorPoint(ccp(0,0));
			tempitem->setPosition(ccp( ((CCString*)dict->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict->objectForKey("y"))->floatValue() ));
			this->addChild(tempitem,2);
			g_coin_bronze.push_back(tempitem);

			if(!dict)
			{
				break;
			}
		}
	}

	CCTMXObjectGroup * group2 = map->objectGroupNamed("coin_silver");

	if(group2 !=NULL)
	{
		CCArray* objects2 = group2->getObjects();

		CCDictionary* dict2 = NULL;
		CCObject* pObj2 = NULL;

		CCARRAY_FOREACH(objects2,pObj2)
		{
			dict2 = (CCDictionary*)pObj2;

			CCSprite* tempitem = CCSprite::create("130710_coin_silver.png");
			tempitem->setAnchorPoint(ccp(0,0));
			tempitem->setPosition(ccp( ((CCString*)dict2->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict2->objectForKey("y"))->floatValue() ));
			this->addChild(tempitem,2);
			g_coin_silver.push_back(tempitem);

			if(!dict2)
			{
				break;
			}
		}
	}

	CCTMXObjectGroup * group3 = map->objectGroupNamed("coin_gold");

	if(group3 !=NULL)
	{
		CCArray* objects3 = group3->getObjects();

		CCDictionary* dict3 = NULL;
		CCObject* pObj3 = NULL;

		CCARRAY_FOREACH(objects3,pObj3)
		{
			dict3 = (CCDictionary*)pObj3;


			CCSprite* tempitem = CCSprite::create("130710_coin_gold.png");
			tempitem->setAnchorPoint(ccp(0,0));
			tempitem->setPosition(ccp( ((CCString*)dict3->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict3->objectForKey("y"))->floatValue() ));
			this->addChild(tempitem,2);
			g_coin_gold.push_back(tempitem);

			if(!dict3)
			{
				break;
			}
		}
	}


	CCTMXObjectGroup * group4 = map->objectGroupNamed("mob1");

	if(group4 !=NULL)
	{
		CCArray* objects4 = group4->getObjects();

		CCDictionary* dict4 = NULL;
		CCObject* pObj4 = NULL;

		CCARRAY_FOREACH(objects4,pObj4)
		{
			dict4 = (CCDictionary*)pObj4;

			CCSprite* tempmob = CCSprite::create("object1_edit.png");
			tempmob->setAnchorPoint(ccp(0,0));
			tempmob->setPosition(ccp( ((CCString*)dict4->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict4->objectForKey("y"))->floatValue() ));
			this->addChild(tempmob,2);
			g_moblist.push_back(tempmob);

			if(!dict4)
			{
				break;
			}
		}
	}


	CCTMXObjectGroup * group5 = map->objectGroupNamed("mob2");

	if(group3 !=NULL)
	{
		CCArray* objects5 = group5->getObjects();

		CCDictionary* dict5 = NULL;
		CCObject* pObj5 = NULL;

		CCARRAY_FOREACH(objects5,pObj5)
		{
			dict5 = (CCDictionary*)pObj5;

			CCSprite* tempmob = CCSprite::create("object2_edit.png");
			tempmob->setAnchorPoint(ccp(0,0));
			tempmob->setPosition(ccp( ((CCString*)dict5->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict5->objectForKey("y"))->floatValue() ));
			this->addChild(tempmob,2);
			g_moblist2.push_back(tempmob);

			if(!dict5)
			{
				break;
			}
		}
	}


	CCTMXObjectGroup * group6 = map->objectGroupNamed("object");

	if(group6 !=NULL)
	{
		CCArray* objects6 = group6->getObjects();

		CCDictionary* dict6 = NULL;
		CCObject* pObj6 = NULL;

		CCARRAY_FOREACH(objects6,pObj6)
		{
			dict6 = (CCDictionary*)pObj6;

			CCSprite* tempobject = CCSprite::create("130710_4.png");
			tempobject->setAnchorPoint(ccp(0,0));
			tempobject->setPosition(ccp( ((CCString*)dict6->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict6->objectForKey("y"))->floatValue() ));
			this->addChild(tempobject,2);
			g_object.push_back(tempobject);

			if(!dict6)
			{
				break;
			}
		}
	}



	CCTMXObjectGroup * group7 = map->objectGroupNamed("floor");

	if(group7 !=NULL)
	{
		CCArray* objects7 = group7->getObjects();

		CCDictionary* dict7 = NULL;
		CCObject* pObj7 = NULL;

		CCARRAY_FOREACH(objects7,pObj7)
		{
			dict7 = (CCDictionary*)pObj7;
			g_floor.push_back(ccp( ((CCString*)dict7->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict7->objectForKey("y"))->floatValue() ));
			if(!dict7)
			{
				break;
			}
		}
	}
	CCTMXObjectGroup * group8 = map->objectGroupNamed("death_block");

	if(group8 !=NULL)
	{
		CCArray* objects8 = group8->getObjects();

		CCDictionary* dict8 = NULL;
		CCObject* pObj8 = NULL;

		CCARRAY_FOREACH(objects8,pObj8)
		{
			dict8 = (CCDictionary*)pObj8;
			g_death_block.push_back(ccp( ((CCString*)dict8->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict8->objectForKey("y"))->floatValue() ));
			if(!dict8)
			{
				break;
			}
		}
	}

	CCTMXObjectGroup * group9 = map->objectGroupNamed("boss");

	if(group9 !=NULL)
	{
		CCArray* objects9 = group9->getObjects();

		CCDictionary* dict9 = NULL;
		CCObject* pObj9 = NULL;

		CCARRAY_FOREACH(objects9,pObj9)
		{
			dict9 = (CCDictionary*)pObj9;

			g_boss = CCSprite::create("Ob_stage1_object_boss.png.png");
			g_boss->setAnchorPoint(ccp(0,0));
			g_boss->setPosition(ccp( ((CCString*)dict9->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict9->objectForKey("y"))->floatValue() ));
			this->addChild(g_boss,2);

			if(!dict9)
			{
				break;
			}
		}
	}

	
	CCTMXObjectGroup * group10 = map->objectGroupNamed("item_huge");

	if(group10 !=NULL)
	{
		CCArray* objects10 = group10->getObjects();

		CCDictionary* dict10 = NULL;
		CCObject* pObj10 = NULL;

		CCARRAY_FOREACH(objects10,pObj10)
		{
			dict10 = (CCDictionary*)pObj10;

		
			CCSprite* tempobject = CCSprite::create("Ig_item_huge.png");
			tempobject->setAnchorPoint(ccp(0,0));
			tempobject->setPosition(ccp( ((CCString*)dict10->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict10->objectForKey("y"))->floatValue() ));
			this->addChild(tempobject,2);
			g_huge_item.push_back(tempobject);

			if(!dict10)
			{
				break;
			}
		}
	}

	
	CCTMXObjectGroup * group11 = map->objectGroupNamed("item_coin");

	if(group11 !=NULL)
	{
		CCArray* objects11 = group11->getObjects();

		CCDictionary* dict11 = NULL;
		CCObject* pObj11 = NULL;

		CCARRAY_FOREACH(objects11,pObj11)
		{
			dict11 = (CCDictionary*)pObj11;

		
			CCSprite* tempobject = CCSprite::create("Ig_item_coin.png");
			tempobject->setAnchorPoint(ccp(0,0));
			tempobject->setPosition(ccp( ((CCString*)dict11->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict11->objectForKey("y"))->floatValue() ));
			this->addChild(tempobject,2);
			g_coin_item.push_back(tempobject);

			if(!dict11)
			{
				break;
			}
		}
	}

	
	CCTMXObjectGroup * group12 = map->objectGroupNamed("item_run");

	if(group12 !=NULL)
	{
		CCArray* objects12 = group12->getObjects();

		CCDictionary* dict12 = NULL;
		CCObject* pObj12 = NULL;

		CCARRAY_FOREACH(objects12,pObj12)
		{
			dict12 = (CCDictionary*)pObj12;

			
			CCSprite* tempobject = CCSprite::create("Ig_item_run.png");
			tempobject->setAnchorPoint(ccp(0,0));
			tempobject->setPosition(ccp( ((CCString*)dict12->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict12->objectForKey("y"))->floatValue() ));
			this->addChild(tempobject,2);
			g_run_item.push_back(tempobject);
			if(!dict12)
			{
				break;
			}
		}
	}

	
	CCTMXObjectGroup * group13 = map->objectGroupNamed("item_magnet");

	if(group13 !=NULL)
	{
		CCArray* objects13 = group13->getObjects();

		CCDictionary* dict13 = NULL;
		CCObject* pObj13 = NULL;

		CCARRAY_FOREACH(objects13,pObj13)
		{
			dict13 = (CCDictionary*)pObj13;

			CCSprite* tempobject = CCSprite::create("Ig_item_magnet.png");
			tempobject->setAnchorPoint(ccp(0,0));
			tempobject->setPosition(ccp( ((CCString*)dict13->objectForKey("x"))->floatValue() + 7500*i, ((CCString*)dict13->objectForKey("y"))->floatValue() ));
			this->addChild(tempobject,2);
			g_magnet_item.push_back(tempobject);

			if(!dict13)
			{
				break;
			}
		}
	}


}

void GameScene::magneticEffect()
{

	CCPoint item_P;
	CCPoint char_P ;
	CCSprite* temp;
	float multyX=0;
	float multyY=0;

	for(g_magnet_item_iterator = g_magnet_item.begin();g_magnet_item_iterator != g_magnet_item.end();)
	{
		bool bDeleted = false;

		temp = *(g_magnet_item_iterator);

		char_P = m_character->getPosition();
		item_P = temp->getPosition();


		if(item_P.x <= char_P.x+g_char->getWidth() && item_P.x>=char_P.x && item_P.y >=char_P.y &&item_P.y<=char_P.y+g_char->getHeight())
		{
			g_checkmagnetic = true;
			g_loadtime = g_checktime;
			bDeleted = true;
		}

		if(!bDeleted)
		{
			g_magnet_item_iterator++;
		}

	}

	if(g_checkmagnetic == true)
	{


		if( (g_checktime - g_loadtime) == 3.3)
		{
			g_checkmagnetic = false;
			return;
		}

		for(g_item_iterator = g_itemlist.begin(); g_item_iterator != g_itemlist.end(); )
		{
			bool bDeleted2 = false;

			temp = *(g_item_iterator);

			char_P = m_character->getPosition();
			item_P = temp->getPosition();

			multyX = (char_P.x+g_char->getWidth()) - (item_P.x+22.5);
			if(multyX <0)	multyX = multyX*(-1);
			multyY = (char_P.y+g_char->getHeight()) - (item_P.y+22.5);
			if(multyY<0)	multyY = multyY*(-1);

			if(multyX*multyX + multyY*multyY < 500*500)
			{
				temp->setPosition(ccp(item_P.x-multyX/10,item_P.y-multyY/10));

				bDeleted2 = true;
			}


			if (!bDeleted2)
			{
				g_item_iterator++;
			}

		}

	}
}

int GameScene::checkTime()
{
	g_temptime++;

	return g_temptime;

}

void GameScene::scoreUpdate()
{
	pNum->cleanup();
	g_score = g_score_item*10 + g_score_mob1*100 + g_score_mob2*200;
	pNum->setString(CCString::createWithFormat("%d", g_score)->m_sString.c_str());


}

void GameScene::scoreInit()
{
	g_score=0;
	g_score_item=0;
	g_score_mob1=0;
	g_score_mob2=0;
	g_score_run=0;


	CCSprite* score_name= CCSprite::create("130827_score.png");
	score_name->setAnchorPoint(ccp(0,0));
	score_name->setPosition(ccp(0,650));
	this->addChild(score_name,3);

	CCSprite* score_bar = CCSprite::create("130827_score2.png");
	score_bar->setAnchorPoint(ccp(0,0));
	score_bar->setPosition(ccp(20,605));
	this->addChild(score_bar,2);

	pNum = CCLabelAtlas::create("0123456789", "number_sprite.png", 31, 40, '0');
	pNum->setAnchorPoint(ccp(0,0));
	pNum->setPosition(ccp(94,625));
	pNum->setString(CCString::createWithFormat("%d", g_score)->m_sString.c_str());

	this->addChild(pNum,3);
}

void GameScene::gameOver()
{
	g_char->runDeadAnimation();

	CCSprite* gameover = CCSprite::create("fail.png");
	gameover->setAnchorPoint(ccp(0,0));
	gameover->setPosition(ccp(0,0));
	this->addChild(gameover,5);

	CCSprite* restart= CCSprite::create("replay.png");
	restart->setAnchorPoint(ccp(0,0));
	restart->setPosition(ccp(895,228));
	this->addChild(restart,6);

	CCSprite* mainmenu= CCSprite::create("gotomenu.png");
	mainmenu->setAnchorPoint(ccp(0,0));
	mainmenu->setPosition(ccp(895,109));
	this->addChild(mainmenu,6);

	g_gameOverCheck = true;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

	this->unschedule(schedule_selector(GameScene::update));

}

void GameScene::pause()
{
	CCSprite* getter ;
	getter = (CCSprite*)this->getChildByTag(tag_pause);

	/*
	a->setAmplitudeRate(1.2);
	a->setDuration(0.2);
	*/
	CCSprite* pause = CCSprite::create("pause.png");
	pause->setAnchorPoint(ccp(0,0));
	pause->setPosition(ccp(0,0));
	this->addChild(pause,6,tag_pauseScene);

	CCSprite* contin = CCSprite::create("countinue.png");
	contin->setAnchorPoint(ccp(0,0));
	contin->setPosition(ccp(895, 411));
	this->addChild(contin,7,tag_continue);

	CCSprite* mainmenu = CCSprite::create("gotomenu.png");
	mainmenu->setAnchorPoint(ccp(0,0));
	mainmenu->setPosition(ccp(895, 296));
	this->addChild(mainmenu,7,tag_goToMenu);

	CCSprite* sound = CCSprite::create("sound_on.png");
	sound->setAnchorPoint(ccp(0,0));
	sound->setPosition(ccp(895,181));
	this->addChild(sound,7,tag_soundControl);

	CCSprite* bgm = CCSprite::create("BGM_on.png");
	bgm->setAnchorPoint(ccp(0,0));
	bgm->setPosition(ccp(895,65));
	this->addChild(bgm,7,tag_bgmControl);
}

void GameScene::endStage()
{
	m_character->stopAllActions();
	this->removeChild(m_character);

	CCSprite* missionComplete = CCSprite::create("success.png");
	missionComplete->setAnchorPoint(ccp(0,0));
	missionComplete->setPosition(ccp(0,0));
	this->addChild(missionComplete,5);

	CCSprite* mainmenu= CCSprite::create("gotomenu.png");
	mainmenu->setAnchorPoint(ccp(0,0));
	mainmenu->setPosition(ccp(895,228));
	this->addChild(mainmenu,6);

	CCSprite* next= CCSprite::create("next.png");
	next->setAnchorPoint(ccp(0,0));
	next->setPosition(ccp(895,109));
	this->addChild(next,6);

	CCLabelAtlas* lastScore =CCLabelAtlas::create("0123456789", "number_sprite.png", 31, 40, '0');;
	lastScore->setAnchorPoint(ccp(0,0));
	lastScore->setPosition(ccp(1120,349));
	lastScore->setString(CCString::createWithFormat("%d", g_score)->m_sString.c_str());
	this->addChild(lastScore,7);
	g_gameSuccess = true;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

	this->unschedule(schedule_selector(GameScene::update));
}