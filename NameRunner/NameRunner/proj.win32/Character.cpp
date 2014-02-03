#include "Character.h"

Character::Character(CCSprite* g_character,int width,int height)
{
	m_character = g_character;
	gravity = 0.7f;
	v=0;
	a= gravity;
	c_click = 0;
	char_P = m_character->getPosition();
	floor_check = 0;
	c_width = 140;
	c_height = 160;
	c_checkanimation = 0;
	animationInit();

	m_characterWidth = width;
	m_characterHeight = height;
}

void Character::Accel()
{
	char_P = m_character->getPosition();
	

	if(floor_check ==0)
	{
		if(char_P.y <=120 && v<6)
		{
			v=0;
			c_click = 0;

			//Character Jump Pixel (430,153.300018~153.4)
			//Character Double Jump Pixel(650,306.600006)
			//Mob Jump Pixel(140,15.400009)
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
	if(c_click<=2)
	{
		v= jump_v;
	}
	//c_click = g_click;

}

void Character::mobjump()
{
	v= 5;
}

void Character::setClick(int g_click)
{
	if(c_click<=2)
	{
		c_click ++;
		
	}
}

int Character::getClick()
{

	return c_click;
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
	return c_width;
}

int Character::getHeight()
{
	return c_height;
}

void Character::setWidth(int width)
{
	c_width = width;
}

void Character::setHeight(int height)
{
	c_height = height;
}

int Character::getCharSpeed()
{
	return v;
	
}

void Character::animationInit()
{
	CCTexture2D *texture;
	CCSpriteFrame *frame0 ;
	CCSpriteFrame *frame1 ;
	CCSpriteFrame *frame2 ;
	CCSpriteFrame *frame3 ;
	CCSpriteFrame *frame4 ;
	CCSpriteFrame *frame5 ;
	CCSpriteFrame *frame6 ;
	CCSpriteFrame *frame7 ;
	CCSpriteFrame *frame8 ;
	CCSpriteFrame *frame9 ;
	CCSpriteFrame *frame10;
	
	switch(global_charSet)
	{

	case 1:
		texture = CCTextureCache::sharedTextureCache()->addImage("Char_Ring.png");

		frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(0,0,130,160));
		frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140,0,140,160));
		frame2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(280,0,140,160));
		frame3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(420,0,140,160));

		frame4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(560,0,185,160));
		frame5 = CCSpriteFrame::createWithTexture(texture, CCRectMake(745,0,185,160));
		frame6 = CCSpriteFrame::createWithTexture(texture, CCRectMake(930,0,185,160));
		frame7 = CCSpriteFrame::createWithTexture(texture, CCRectMake(1115,0,185,160));
		frame8 = CCSpriteFrame::createWithTexture(texture, CCRectMake(1300,0,185,160));

		frame9 = CCSpriteFrame::createWithTexture(texture, CCRectMake(1486,0,185,160));
		frame10 = CCSpriteFrame::createWithTexture(texture, CCRectMake(1670,0,185,160));

		break;
	case 2:
		texture = CCTextureCache::sharedTextureCache()->addImage("Char_pinok2.png");
		frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*0,0,115,160));
		frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*1,0,115,160));
		frame2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*2,0,115,160));
		frame3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*3,0,115,160));
		frame4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*4,0,115,160));
		frame5 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*5,0,115,160));
		frame6 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*6,0,115,160));
		frame7 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*7,0,115,160));
		frame8 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*8,0,115,160));
		frame9 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*9,0,115,160));
		frame10 = CCSpriteFrame::createWithTexture(texture, CCRectMake(115*10,0,115,160));
		
		break;
	case 3:
		break;
	default:
		texture = CCTextureCache::sharedTextureCache()->addImage("Char_Captain_nine_oclock.png");
		// manually add frames to the frame cache
		frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*0,0,140,160));
		frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*1,0,140,160));
		frame2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*2,0,140,160));
		frame3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*3,0,140,160));
		frame4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*4,0,140,160));
		frame5 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*5,0,140,160));
		frame6 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*6,0,140,160));
		frame7 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*7,0,140,160));
		frame8 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*8,0,140,160));
		frame9 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*9,0,140,160));
		frame10 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*10,0,140,160));

		break;
	}
	

		CCArray* animFrames0 = CCArray::createWithCapacity(6);
		animFrames0->addObject(frame0);
		animFrames0->addObject(frame1);

		CCArray* animFrames1 = CCArray::createWithCapacity(6);
		animFrames1->addObject(frame2);

		CCArray* animFrames2 = CCArray::createWithCapacity(6);
		animFrames2->addObject(frame3);
		animFrames2->addObject(frame4);
		animFrames2->addObject(frame5);
		animFrames2->addObject(frame6);
		animFrames2->addObject(frame7);
		animFrames2->addObject(frame8);


		CCArray* animFrames3 = CCArray::createWithCapacity(2);
		animFrames3 ->addObject(frame9);
		animFrames3 ->addObject(frame10);

		CCAnimation * animation0 = CCAnimation::createWithSpriteFrames(animFrames0, 0.1f);
		CCAnimate *animate0 = CCAnimate::create(animation0);
		CCActionInterval* seq0 = CCSequence::create( animate0,NULL);

		CCAnimation *  animation1 = CCAnimation::createWithSpriteFrames(animFrames1, 0.1f);
		CCAnimate *animate1 = CCAnimate::create(animation1);
		CCActionInterval* seq1 = CCSequence::create( animate1,NULL);

		CCAnimation * animation2 = CCAnimation::createWithSpriteFrames(animFrames2, 0.1f);
		CCAnimate *animate2 = CCAnimate::create(animation2);
		CCActionInterval* seq2 = CCSequence::create( animate2,NULL);

		CCAnimation* animation3 = CCAnimation::createWithSpriteFrames(animFrames3,0.1f);
		CCAnimate *animate3 = CCAnimate::create(animation3);

		runact   = CCRepeatForever::create(seq0);
		jump1act = CCRepeatForever::create(seq1);
		jump2act = CCRepeatForever::create(seq2);
		deadact = CCRepeat::create(animate3,1);
}

void Character::animationCreate()
{	CCTexture2D *texture;
	CCSpriteFrame *frame0 ;
	CCSpriteFrame *frame1 ;
	CCSpriteFrame *frame2 ;
	CCSpriteFrame *frame3 ;
	CCSpriteFrame *frame4 ;
	CCSpriteFrame *frame5 ;
	CCSpriteFrame *frame6 ;
	CCSpriteFrame *frame7 ;
	CCSpriteFrame *frame8 ;
	CCSpriteFrame *frame9 ;
	CCSpriteFrame *frame10;
	
	switch(global_charSet)
	{

	case 1:
		texture = CCTextureCache::sharedTextureCache()->addImage("Char_Ring.png");

		frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(0,0,130,160));
		frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140,0,140,160));
		frame2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(280,0,140,160));
		frame3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(420,0,140,160));

		frame4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(560,0,185,160));
		frame5 = CCSpriteFrame::createWithTexture(texture, CCRectMake(745,0,185,160));
		frame6 = CCSpriteFrame::createWithTexture(texture, CCRectMake(930,0,185,160));
		frame7 = CCSpriteFrame::createWithTexture(texture, CCRectMake(1115,0,185,160));
		frame8 = CCSpriteFrame::createWithTexture(texture, CCRectMake(1300,0,185,160));

		frame9 = CCSpriteFrame::createWithTexture(texture, CCRectMake(1486,0,185,160));
		frame10 = CCSpriteFrame::createWithTexture(texture, CCRectMake(1670,0,185,160));

		break;
	case 2:
		break;
	case 3:
		break;
	default:
		texture = CCTextureCache::sharedTextureCache()->addImage("main character.png");
		// manually add frames to the frame cache
		frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*0,0,140,160));
		frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*1,0,140,160));
		frame2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*2,0,140,160));
		frame3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*3,0,140,160));
		frame4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*4,0,140,160));
		frame5 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*5,0,140,160));
		frame6 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*6,0,140,160));
		frame7 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*7,0,140,160));
		frame8 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*8,0,140,160));
		frame9 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*9,0,140,160));
		frame10 = CCSpriteFrame::createWithTexture(texture, CCRectMake(140*10,0,140,160));

		break;
	}
	

		CCArray* animFrames0 = CCArray::createWithCapacity(6);
		animFrames0->addObject(frame0);
		animFrames0->addObject(frame1);

		CCArray* animFrames1 = CCArray::createWithCapacity(6);
		animFrames1->addObject(frame2);

		CCArray* animFrames2 = CCArray::createWithCapacity(6);
		animFrames2->addObject(frame3);
		animFrames2->addObject(frame4);
		animFrames2->addObject(frame5);
		animFrames2->addObject(frame6);
		animFrames2->addObject(frame7);
		animFrames2->addObject(frame8);


		CCArray* animFrames3 = CCArray::createWithCapacity(2);
		animFrames3 ->addObject(frame9);
		animFrames3 ->addObject(frame10);



    CCAnimation * animation0 = CCAnimation::createWithSpriteFrames(animFrames0, 0.1f);
    CCAnimate *animate0 = CCAnimate::create(animation0);
    c_seq0 = CCSequence::create( animate0,NULL);

	CCAnimation *  animation1 = CCAnimation::createWithSpriteFrames(animFrames1, 0.1f);
    CCAnimate *animate1 = CCAnimate::create(animation1);
    c_seq1 = CCSequence::create( animate1,NULL);

	CCAnimation * animation2 = CCAnimation::createWithSpriteFrames(animFrames2, 0.1f);
    CCAnimate *animate2 = CCAnimate::create(animation2);
    c_seq2 = CCSequence::create( animate2,NULL);


	CCAnimation* animation3 = CCAnimation::createWithSpriteFrames(animFrames3,0.1f);
	c_animate3 = CCAnimate::create(animation3);

	runact   = CCRepeatForever::create(c_seq0);
	runact->setTag(1);
	jump1act = CCRepeatForever::create(c_seq1);
	jump1act->setTag(2);
	jump2act = CCRepeatForever::create(c_seq2);
	jump2act->setTag(3);
	deadact = CCRepeat::create(c_animate3,1);
	deadact->setTag(4);

}

void Character::animationControl()
{
	
	int click = c_click;

	switch(click)
	{
	case 0:

		if(c_checkanimation ==0)
		{
			animationCreate();
			m_character->cleanup();
			m_character->runAction(runact);
			c_checkanimation = 1;
		}

		break;
	case 1:
		if(c_checkanimation == 1)
		{
			m_character->cleanup();
			animationCreate();
			m_character->runAction(jump1act);
			c_checkanimation = 2;
		}
		
		break;
	case 2:
		if(c_checkanimation == 2)
		{
			
			m_character->cleanup();
			animationCreate();
			m_character->runAction(jump2act);
			c_checkanimation = 10;
		}
		break;


	default:
		break;
	}
 }


int Character::getCheckAnimation()
{
	return c_checkanimation;
}

void Character::setCheckAniamtion(int checkanimation)
{
	c_checkanimation = checkanimation;
}


void Character::runDeadAnimation()
{
	m_character->cleanup();
	animationCreate();
	m_character->runAction(deadact);
}


void Character::runRunAniamtion()
{
	m_character->cleanup();
	animationCreate();
	m_character->runAction(runact);
}

void Character::runJump1Animation()
{
	m_character->cleanup();
	animationCreate();
	m_character->runAction(jump1act);
}

void Character::runJump2Animation()
{
	m_character->cleanup();
	animationCreate();
	m_character->runAction(jump2act);
}