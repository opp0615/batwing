#include "Character.h"

Character::Character(CCSprite* g_character)
{
	m_character = g_character;
	gravity = 0.3f;
	v=0;
	a= gravity;
	m_click = 0;
	char_P = m_character->getPosition();
	floor_check = 0;
	width = 140;
	height = 160;
	bani = false;
}

void Character::Accel()
{
	char_P = m_character->getPosition();
	

	if(floor_check ==0)
	{
		if(char_P.y <=100 && v<6)
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

	else
	{
	
		v -=a;
		m_character->setPositionY(char_P.y+v);

		if(char_P.y>=200)
		{
			setfloorcheck(0);
		}

	}
	
	
}

void Character::setJump(float jump_v)
{
	if(m_click<=2)
	{
		v= jump_v;
	}
	//m_click = g_click;

}

void Character::mobjump()
{
	v= 10;
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

CCSprite* Character::getChar()
{
	return m_character;

}

void Character::setfloorcheck(int g_floor_check)
{
	floor_check = g_floor_check;

}

int Character::getWidth()
{
	return width;
}

int Character::getHeight()
{
	return height;
}

int Character::getCharSpeed()
{
	return v;
	
}
