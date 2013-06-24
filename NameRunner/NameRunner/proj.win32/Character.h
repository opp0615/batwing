#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class Character {
private:
	CCPoint char_P;
	CCSprite* m_character;
	
	float count;
	float v;
	float a;
	float gravity;
	float m_acell;
	int collision;
	int m_random_Map1,m_random_Map2 ,temp_randomMap;
	bool m_mod;
	int m_game_speed;
	int m_click;

public:
	Character(CCSprite* g_character);
	//bool getMod();
	//void CheckCollision();
	//void getcollisionArray(int getcollision[][480]);
	//void setRandomMap(int radom_Map1 ,int random_Map2); 
	//void Accel();
	void Accel();
	void SetAccel(float acell);
	void getGameSpeed(int game_speed);
	void setJump(float jump_v);
	void setClick(int g_click);
	CCSprite* getChar();
	int getClick();
};