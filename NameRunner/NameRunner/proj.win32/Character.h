#pragma once

#include "cocos2d.h"
#include "global.h"
using namespace cocos2d;

class Character {
private:
	CCPoint char_P;
	CCSprite* m_character;
	int m_characterWidth,m_characterHeight;
	float count;
	float v;
	float a;
	float gravity;
	float m_acell;
	int c_width,c_height;
	int collision;
	int m_random_Map1,m_random_Map2 ,temp_randomMap;
	bool m_mod;
	int m_game_speed;
	int c_click;
	


	CCActionInterval* c_seq0;
	CCActionInterval* c_seq1;
	CCActionInterval* c_seq2;
	CCAnimate* c_animate3;

	CCAction* runact;
	CCAction* jump1act;
	CCAction* jump2act;
	CCAction* deadact;

	int c_checkanimation;
	int floor_check;

public:
	Character(CCSprite* g_character,int width,int height);
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
	void Animation();
	int getCharSpeed();
	CCSprite* getChar();
	int getClick();
	void setfloorcheck(int g_floor_check);

	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);

	void charani();
	void mobjump();
	void animationControl();
	void animationCreate();
	void animationInit();

	int getCheckAnimation();
	void setCheckAniamtion(int checkanimation);
	void runDeadAnimation();
	void runRunAniamtion();
	void runJump1Animation();
	void runJump2Animation();
};