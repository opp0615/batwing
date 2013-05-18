#include "Character.h"

Character::Character(CCSprite* g_character)
{
	m_character = g_character;
	gravity = 0.2f;
	v=0;
	a= gravity;
	m_click = 0;
	char_P = m_character->getPosition();
}

void Character::Accel()
{
	char_P = m_character->getPosition();
	if(char_P.y <=300 && v<3)
	{
		v=0;
		m_click = 0;
	}
	else 
	{
		v -=a;
	}
	
	m_character->setPositionY(char_P.y+v);
	
	
}

void Character::setJump(float jump_v)
{
	if(m_click<=2)
	{
		v= jump_v;
	}
	//m_click = g_click;

}

void Character::setClick(int g_click)
{
	if(m_click<=2)
	{
		m_click ++;
	}
}

int Character::getClick()
{

	return m_click;
}