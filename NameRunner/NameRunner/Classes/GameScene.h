#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "global.h"
#include "Character.h"
#include "Map.h"
#include "itemManager.h"
#include "MainmenuScene.h"

#include <list>

#include "SimpleAudioEngine.h"
using namespace cocos2d;



class GameScene : public cocos2d::CCLayerColor
{
private:
	Character* g_char;
	Map* g_map;
	itemManager* g_itemManager;
	int g_click;
	int game_speed;
	int scroll_count;
	CCSprite* m_character;
	CCSprite* nowpositionpoint ;
	int banimation;

	CCLabelAtlas *pNum;

	bool g_gameOverCheck;
	bool g_gameSuccess;
	bool g_pauseClick;
	
	//시간체크
	float g_checktime;
	int g_temptime;
	float g_loadtime;

	//스코어
	int g_score;
	int g_score_coinBronze;
	int g_score_coinSilver;
	int g_score_coinGold;
	int g_score_mob1;
	int g_score_mob2;
	int g_score_run;
	int g_viewingScene;

	int gameEndZone;

	float g_magneticAccelConst;//자석 가속도 상수
	bool g_checkmagnetic;//자석 온오프

	CCAction* runact;
	CCAction* jump1act;
	CCAction* jump2act;

	CCAction* deadact;

	CCTMXTiledMap* map_level[10];//맵

	int pauseCheckAni;

	int GridX,GridY;
	CCPoint g_virtual_char;//가상위치

	std::list<CCSprite*> g_itemlist;
	std::list<CCSprite*>::iterator g_item_iterator;

	//coin

	std::list<CCSprite*> g_coin_bronze;
	std::list<CCSprite*>::iterator g_coin_bronze_iterator;

	std::list<CCSprite*> g_coin_silver;
	std::list<CCSprite*>::iterator g_coin_silver_iterator;

	std::list<CCSprite*> g_coin_gold;
	std::list<CCSprite*>::iterator g_coin_gold_iterator;

	//object

	std::list<CCSprite*> g_moblist;
	std::list<CCSprite*>::iterator g_mob_iterator;

	std::list<CCSprite*> g_moblist2;
	std::list<CCSprite*>::iterator g_mob_iterator2;

	std::list<CCSprite*> g_object;
	std::list<CCSprite*>::iterator g_object_iterator;


	//item
	std::list<CCSprite*> g_huge_item;
	std::list<CCSprite*>::iterator g_huge_item_iterator;

	std::list<CCSprite*> g_run_item;
	std::list<CCSprite*>::iterator g_run_item_iterator;

	std::list<CCSprite*> g_coin_item;
	std::list<CCSprite*>::iterator g_coin_item_iterator;

	std::list<CCSprite*> g_magnet_item;
	std::list<CCSprite*>::iterator g_magnet_item_iterator;

	CCSprite* g_boss;
	CCSprite* g_mob1;
	CCSprite* g_mob2;
	CCSprite* g_deathObject;

	//floorcheck

	std::list<CCPoint> g_floor;
	std::list<CCPoint>::iterator g_floor_iterator;

	std::list<CCPoint> g_death_block;
	std::list<CCPoint>::iterator g_death_block_iterator;

public:

	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	virtual void ccTouchesBegan(CCSet* touches,CCEvent* event);
	//virtual void ccTouchesEnded(CCSet* touches,CCEvent* evnet);

	void update(float dt);

	void mapdataload(CCTMXTiledMap* map,int i);

	void collisionCheck();

	void itemScrolling();

	void mobScrolling();

	void mapScrolling();

	void mapInit();

	void gameOver();

	void floorcheck();

	void pause();

	void charInit();
	
	void map1create();

	void map2create();

	void callBackRemoveEffect(CCNode* sender);

	void animationControl();

	void animationcreate();

	void magneticEffect();

	int checkTime();

	void objectDataClear();

	void scoreUpdate();

	void scoreInit();

	void soundInit();

	void endStage();
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif  // __GAME_SCENE_H__