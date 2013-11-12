#pragma once
#include "cocos2d.h"
#include <list>

using namespace cocos2d;

class itemManager{
private:
	int width,height;
	std::list<CCSprite*> m_itemlist;
public:
	itemManager();
	void additem(CCSprite* g_item);
};
