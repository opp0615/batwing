#include "Map.h"

Map::Map(CCSprite* g_map1,CCSprite* g_map2)
{
	m_map1 = g_map1;
	m_map2 = g_map2;
}

void Map::Scrolling()
{
	CCPoint map1_P;
	CCPoint map2_P;

	map1_P = m_map1->getPosition();
	map2_P = m_map2->getPosition();
	
	m_map1->setPositionX(map1_P.x-3);
	m_map2->setPositionX(map2_P.x-3);
	if(map1_P.x<= -1280 || map2_P.x<=0)
	{
		CCSprite* temp;

		temp = m_map1;
		m_map1 = m_map2;
		m_map2 = temp;
		
		m_map2->setPositionX(1280);
	}

}