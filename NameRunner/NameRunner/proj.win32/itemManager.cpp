#include "itemManager.h"

itemManager::itemManager()
{
	
}

void itemManager::additem(CCSprite* g_item)
{
	m_itemlist.push_back(g_item);
	
}

