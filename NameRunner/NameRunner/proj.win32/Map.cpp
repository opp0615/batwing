#include "Map.h"

Map::Map(CCSprite* g_map1,CCSprite* g_map2,int g_game_speed)
{
	m_map1 = g_map1;
	m_map2 = g_map2;
	m_game_speed = g_game_speed-8;
	width = 2000;
	height = 720;

	m_map1->setPosition(ccp(0,0));
	m_map2->setPosition(ccp(width-10,0));
}

void Map::Scrolling()
{
	CCPoint map1_P;
	CCPoint map2_P;

	map1_P = m_map1->getPosition();
	map2_P = m_map2->getPosition();
	
	m_map1->setPositionX(map1_P.x-m_game_speed);
	m_map2->setPositionX(map2_P.x-m_game_speed);
	if(map1_P.x<= -width || map2_P.x<=0)
	{
		CCSprite* temp;

		temp = m_map1;
		m_map1 = m_map2;
		m_map2 = temp;
		
		m_map2->setPositionX(width-10);
	}

}

CCSprite* Map::getMap(int n)
{
	if(n==1)	return m_map1;
	else return m_map2;

}