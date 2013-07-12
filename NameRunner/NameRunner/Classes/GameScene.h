#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Character.h"
#include "Map.h"
#include "itemManager.h"

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
	CCTMXTiledMap* floor_test1;
	CCTMXTiledMap* floor_test2;

	int GridX,GridY;

	std::list<CCSprite*> g_itemlist;
	std::list<CCSprite*>::iterator g_item_iterator;

	std::list<CCSprite*> g_moblist;
	std::list<CCSprite*>::iterator g_mob_iterator;

	std::list<CCPoint> g_floor;
	std::list<CCPoint>::iterator g_floor_iterator;

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

	void createItem();

	void collisionCheck();

	void itemScrolling();

	void createmob();

	void mobScrolling();

	void mapScrolling();

	void mapInit();

	void floorcheck();

	void charInit();
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif  // __GAME_SCENE_H__