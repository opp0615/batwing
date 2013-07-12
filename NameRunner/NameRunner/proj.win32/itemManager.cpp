#include "itemManager.h"

itemManager::itemManager()
{
	width = 55;
	height = 55;
}

void itemManager::additem(CCSprite* g_item)
{
	m_itemlist.push_back(g_item);
	
}

