#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class Map {

private:
	CCSprite* m_map1;
	CCSprite* m_map2;
	int m_game_speed;
	int width,height;
public:
	Map(CCSprite* g_map1,CCSprite* g_map2,int g_game_speed);
	
	void Scrolling();
	CCSprite* getMap(int n);
};