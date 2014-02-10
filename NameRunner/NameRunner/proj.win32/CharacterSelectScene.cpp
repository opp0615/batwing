#include "CharacterSelectScene.h"

#define tag_subway 11
#define tag_ring 22
#define tag_pinok 33
#define tag_livingDead 44
#define tag_popUp 88
#define tag_leftButton 37 //거꾸로해도 소수가 되는 신비한 수 왼쪽 오른쪽이라 정의한다!
#define tag_rightButton 73

#define subway_width 200
#define subway_height 200
#define ring_width 200
#define ring_height 200
#define pinok_width 200
#define pinok_height 200
#define livingDead_width 200
#define livingDead_height 200

#define leftButton_width 96
#define leftButton_height 62
#define rightButton_width 96
#define rightButton_height 62


CCScene* CharacterSelectScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		CharacterSelectScene *layer = CharacterSelectScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

bool CharacterSelectScene::init()
{
	if ( CCLayer::init() )
	{

		if (! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}

		subwayStateFinding(global_subwayState);
		ringStateFinding(global_ringState);
		pinokStateFinding(global_pinokState);
		livingDeadStateFinding(global_livingDeadState);

		global_charSet = 0;
		m_pressedCharNumber = 0;
		m_popUpState = false;

		CCSprite* background = CCSprite::create("CharacterSelect.png");
		background->setAnchorPoint(ccp(0,0));
		background->setPosition(ccp(0,0));
		this->addChild(background,1);

		CCSprite* backScene = CCSprite::create("backscene.png");
		backScene->setAnchorPoint(ccp(0,0));
		backScene->setPosition(ccp(1100,20));
		this->addChild(backScene,3);

		this->setTouchEnabled(true);
	}
	return true;
}

void CharacterSelectScene::ccTouchesBegan(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	if(m_popUpState ==1)
	{
		if(757<=location.x && location.x<=757+leftButton_width && 227<=location.y && location.y<=227+leftButton_height)
		{
			CCSprite* leftButton = (CCSprite*)this->getChildByTag(tag_leftButton);
			leftButton->setTextureRect(CCRect(0,0,leftButton_width,leftButton_height));
		}

		else if(992<=location.x && location.x<=992+rightButton_width && 227<=location.y && location.y<=227+rightButton_height)
		{
			CCSprite* rigthButton = (CCSprite*)this->getChildByTag(tag_rightButton);
			rigthButton->setTextureRect(CCRect(0,0,rightButton_width,rightButton_height));
		}
	}

}


void CharacterSelectScene::ccTouchesEnded(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);


	if(m_popUpState == 0)
	{
		if(1100<=location.x && location.x<=1100 +130 && 20<=location.y&& location.y<=20+130)
		{
			CCScene *pScene = StrategyOfficeScene::scene();
			CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
			CCDirector::sharedDirector()->replaceScene(pTran);
		}

		else if(439<=location.x && location.x<=439+subway_width && 360 <= location.y && location.y <= 360+subway_height)
		{
			charSelectPopUp(0);
		}

		else if(840<=location.x && location.x<=840+ring_width && 360<=location.y && location.y<=360+ring_height)
		{
			charSelectPopUp(1);
		}

		else if(439<=location.x && location.x<=439+pinok_width && 90<=location.y && location.y<=90+pinok_height)
		{
			charSelectPopUp(2);
		}

		else if(840<=location.x && location.x<=840+livingDead_width && 90<=location.y && location.y<=90+livingDead_height)
		{
			charSelectPopUp(3);
		}
	}

	else
	{
		if(757<=location.x && location.x<=757+leftButton_width && 227<=location.y && location.y<=227+leftButton_height)
		{
			switch(m_pressedCharNumber)
			{
			case 0:
				if(global_subwayState==0)
				{
					global_subwayState = 1;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Result_buysomething.wav");
					CCSprite* subway = (CCSprite*)this->getChildByTag(tag_subway);
					subway->setTextureRect(CCRect(subway_width*2,0,subway_width,subway_height));

					this->removeChildByTag(tag_popUp);
					this->removeChildByTag(tag_leftButton);
					this->removeChildByTag(tag_rightButton);
					m_popUpState = 0;
				}

				else
				{
					CCSprite* subway = (CCSprite*)this->getChildByTag(tag_subway);
					subway->setTextureRect(CCRect(subway_width*1,0,subway_width,subway_height));
					global_charSet = 0;
					changingCharWhenPopClosed();					

					this->removeChildByTag(tag_popUp);
					this->removeChildByTag(tag_leftButton);
					this->removeChildByTag(tag_rightButton);
					m_popUpState = 0;
				}
				break;
			case 1:
				if(global_ringState==0)
				{
					global_ringState = 1;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Result_buysomething.wav");
					CCSprite* ring = (CCSprite*)this->getChildByTag(tag_ring);
					ring->setTextureRect(CCRect(ring_width*2,0,ring_width,ring_height));

					this->removeChildByTag(tag_popUp);
					this->removeChildByTag(tag_leftButton);
					this->removeChildByTag(tag_rightButton);
					m_popUpState = 0;
				}

				else
				{
					CCSprite* ring = (CCSprite*)this->getChildByTag(tag_ring);
					ring->setTextureRect(CCRect(ring_width*1,0,ring_width,ring_height));
					global_charSet = 1;
					changingCharWhenPopClosed();

					this->removeChildByTag(tag_popUp);
					this->removeChildByTag(tag_leftButton);
					this->removeChildByTag(tag_rightButton);
					m_popUpState = 0;
				}
				break;
			case 2:
				if(global_pinokState==0)
				{
					global_pinokState = 1;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Result_buysomething.wav");
					CCSprite* pinok = (CCSprite*)this->getChildByTag(tag_pinok);
					pinok->setTextureRect(CCRect(pinok_width*2,0,pinok_width,pinok_height));

					this->removeChildByTag(tag_popUp);
					this->removeChildByTag(tag_leftButton);
					this->removeChildByTag(tag_rightButton);
					m_popUpState = 0;
				}

				else
				{
					CCSprite* pinok = (CCSprite*)this->getChildByTag(tag_pinok);
					pinok->setTextureRect(CCRect(pinok_width*1,0,pinok_width,pinok_height));
					global_charSet = 2;
					changingCharWhenPopClosed();

					this->removeChildByTag(tag_popUp);
					this->removeChildByTag(tag_leftButton);
					this->removeChildByTag(tag_rightButton);
					m_popUpState = 0;
				}
				break;
			case 3:
				if(global_livingDeadState==0)
				{
					global_livingDeadState = 1;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Result_buysomething.wav");
					CCSprite* livingDead = (CCSprite*)this->getChildByTag(tag_livingDead);
					livingDead->setTextureRect(CCRect(livingDead_width*2,0,livingDead_width,livingDead_height));

					this->removeChildByTag(tag_popUp);
					this->removeChildByTag(tag_leftButton);
					this->removeChildByTag(tag_rightButton);
					m_popUpState = 0;
				}

				else
				{
					CCSprite* livingDead = (CCSprite*)this->getChildByTag(tag_livingDead);
					livingDead->setTextureRect(CCRect(livingDead_width*1,0,livingDead_width,livingDead_height));
					global_charSet = 3;
					changingCharWhenPopClosed();

					this->removeChildByTag(tag_popUp);
					this->removeChildByTag(tag_leftButton);
					this->removeChildByTag(tag_rightButton);
					m_popUpState = 0;
				}
				break;
			}
		}

		else if(992<=location.x && location.x<=992+rightButton_width && 227<=location.y && location.y<=227+rightButton_height)
		{
			this->removeChildByTag(tag_popUp);
			this->removeChildByTag(tag_leftButton);
			this->removeChildByTag(tag_rightButton);
			m_popUpState = 0;
		}
	}

}

void CharacterSelectScene::subwayStateFinding(bool state)
{
	if(state == 0)
	{
		CCSprite* subway = CCSprite::create("cs_subwaySprite.png",CCRect(subway_width*0,0,subway_width,subway_height));
		subway->setAnchorPoint(ccp(0,0));
		subway->setPosition(ccp(439,360));
		this->addChild(subway,3,tag_subway);
	}

	else if(state == 1 && global_charSet ==0)
	{
		CCSprite* subway = CCSprite::create("cs_subwaySprite.png",CCRect(subway_width*1,0,subway_width,subway_height));
		subway->setAnchorPoint(ccp(0,0));
		subway->setPosition(ccp(439,360));
		this->addChild(subway,3,tag_subway);
	}

	else if(state == 1 && global_subwayState == 1)
	{
		CCSprite* subway = CCSprite::create("cs_subwaySprite.png",CCRect(subway_width*2,0,subway_width,subway_height));
		subway->setAnchorPoint(ccp(0,0));
		subway->setPosition(ccp(439,360));
		this->addChild(subway,3,tag_subway);
	}

}

void CharacterSelectScene::ringStateFinding(bool state)
{
	if(state == 0)
	{
		CCSprite* ring = CCSprite::create("cs_ringSprite.png",CCRect(ring_height*0,0,ring_width,ring_height));
		ring->setAnchorPoint(ccp(0,0));
		ring->setPosition(ccp(840,360));
		this->addChild(ring,3,tag_ring);
	}

	else if(state == 1 && global_charSet ==1)
	{
		CCSprite* ring = CCSprite::create("cs_ringSprite.png",CCRect(ring_height*1,0,ring_width,ring_height));
		ring->setAnchorPoint(ccp(0,0));
		ring->setPosition(ccp(840,360));
		this->addChild(ring,3,tag_ring);
	}

	else if(state == 1 && global_ringState == 1)
	{
		CCSprite* ring = CCSprite::create("cs_ringSprite.png",CCRect(ring_height*2,0,ring_width,ring_height));
		ring->setAnchorPoint(ccp(0,0));
		ring->setPosition(ccp(840,360));
		this->addChild(ring,3,tag_ring);
	}

}

void CharacterSelectScene::pinokStateFinding(bool state)
{
	if(state == 0)
	{
		CCSprite* pinok = CCSprite::create("cs_pinokSprite.png",CCRect(pinok_width*0,0,pinok_width,pinok_height));
		pinok->setAnchorPoint(ccp(0,0));
		pinok->setPosition(ccp(439,90));
		this->addChild(pinok,3,tag_pinok);
	}

	else if(state == 1 && global_charSet ==2)
	{
		CCSprite* pinok = CCSprite::create("cs_pinokSprite.png",CCRect(pinok_width*1,0,pinok_width,pinok_height));
		pinok->setAnchorPoint(ccp(0,0));
		pinok->setPosition(ccp(439,90));
		this->addChild(pinok,3,tag_pinok);
	}

	else if(state == 1 && global_pinokState == 1)
	{
		CCSprite* pinok = CCSprite::create("cs_pinokSprite.png",CCRect(pinok_width*2,0,pinok_width,pinok_height));
		pinok->setAnchorPoint(ccp(0,0));
		pinok->setPosition(ccp(439,90));
		this->addChild(pinok,3,tag_pinok);
	}

}

void CharacterSelectScene::livingDeadStateFinding(bool state)
{
	if(state == 0)
	{
		CCSprite* livingDead = CCSprite::create("cs_livingdeadSprite.png",CCRect(livingDead_width*0,0,livingDead_width,livingDead_height));
		livingDead->setAnchorPoint(ccp(0,0));
		livingDead->setPosition(ccp(840,90));
		this->addChild(livingDead,3,tag_livingDead);
	}

	else if(state == 1 && global_charSet ==3)
	{
		CCSprite* livingDead = CCSprite::create("cs_livingdeadSprite.png",CCRect(livingDead_width*1,0,livingDead_width,livingDead_height));
		livingDead->setAnchorPoint(ccp(0,0));
		livingDead->setPosition(ccp(840,90));
		this->addChild(livingDead,3,tag_livingDead);
	}

	else if(state == 1 && global_livingDeadState == 1)
	{
		CCSprite* livingDead = CCSprite::create("cs_livingdeadSprite.png",CCRect(livingDead_width*2,0,livingDead_width,livingDead_height));
		livingDead->setAnchorPoint(ccp(0,0));
		livingDead->setPosition(ccp(840,90));
		this->addChild(livingDead,3,tag_livingDead);
	}

}

void CharacterSelectScene::charSelectPopUp(int charset)
{
	m_popUpState =1;
	m_pressedCharNumber = charset;

	if(charset == 0)
	{
		CCSprite* popUp = CCSprite::create("ex_subway.png");
		popUp->setAnchorPoint(ccp(0,0));
		popUp->setPosition(ccp(294,104));
		this->addChild(popUp,5,tag_popUp);

		if(global_subwayState == 0)
		{
			CCSprite* leftButton = CCSprite::create("cs_buy.png",CCRect(leftButton_width,0,leftButton_width,leftButton_height));
			leftButton->setAnchorPoint(ccp(0,0));
			leftButton->setPosition(ccp(757,227));
			this->addChild(leftButton,6,tag_leftButton);

			CCSprite* rightButton = CCSprite::create("cs_cancle.png",CCRect(rightButton_width,0,rightButton_width,rightButton_height));
			rightButton->setAnchorPoint(ccp(0,0));
			rightButton->setPosition(ccp(992,227));
			this->addChild(rightButton,6,tag_rightButton);
		}

		else
		{
			CCSprite* leftButton = CCSprite::create("cs_select.png",CCRect(leftButton_width,0,leftButton_width,leftButton_height));
			leftButton->setAnchorPoint(ccp(0,0));
			leftButton->setPosition(ccp(757,227));
			this->addChild(leftButton,6,tag_leftButton);

			CCSprite* rightButton = CCSprite::create("cs_cancle.png",CCRect(rightButton_width,0,rightButton_width,rightButton_height));
			rightButton->setAnchorPoint(ccp(0,0));
			rightButton->setPosition(ccp(992,227));
			this->addChild(rightButton,6,tag_rightButton);
		}



	}

	else if(charset == 1)
	{
		CCSprite* popUp = CCSprite::create("ex_ring.png");
		popUp->setAnchorPoint(ccp(0,0));
		popUp->setPosition(ccp(294,104));
		this->addChild(popUp,5,tag_popUp);

		if(global_ringState == 0)
		{
			CCSprite* leftButton = CCSprite::create("cs_buy.png",CCRect(leftButton_width,0,leftButton_width,leftButton_height));
			leftButton->setAnchorPoint(ccp(0,0));
			leftButton->setPosition(ccp(757,227));
			this->addChild(leftButton,6,tag_leftButton);

			CCSprite* rightButton = CCSprite::create("cs_cancle.png",CCRect(rightButton_width,0,rightButton_width,rightButton_height));
			rightButton->setAnchorPoint(ccp(0,0));
			rightButton->setPosition(ccp(992,227));
			this->addChild(rightButton,6,tag_rightButton);
		}

		else
		{
			CCSprite* leftButton = CCSprite::create("cs_select.png",CCRect(leftButton_width,0,leftButton_width,leftButton_height));
			leftButton->setAnchorPoint(ccp(0,0));
			leftButton->setPosition(ccp(757,227));
			this->addChild(leftButton,6,tag_leftButton);

			CCSprite* rightButton = CCSprite::create("cs_cancle.png",CCRect(rightButton_width,0,rightButton_width,rightButton_height));
			rightButton->setAnchorPoint(ccp(0,0));
			rightButton->setPosition(ccp(992,227));
			this->addChild(rightButton,6,tag_rightButton);
		}
	}

	else if(charset == 2)
	{
		CCSprite* popUp = CCSprite::create("ex_pinok.png");
		popUp->setAnchorPoint(ccp(0,0));
		popUp->setPosition(ccp(294,104));
		this->addChild(popUp,5,tag_popUp);

		if(global_pinokState == 0)
		{
			CCSprite* leftButton = CCSprite::create("cs_buy.png",CCRect(leftButton_width,0,leftButton_width,leftButton_height));
			leftButton->setAnchorPoint(ccp(0,0));
			leftButton->setPosition(ccp(757,227));
			this->addChild(leftButton,6,tag_leftButton);

			CCSprite* rightButton = CCSprite::create("cs_cancle.png",CCRect(rightButton_width,0,rightButton_width,rightButton_height));
			rightButton->setAnchorPoint(ccp(0,0));
			rightButton->setPosition(ccp(992,227));
			this->addChild(rightButton,6,tag_rightButton);
		}

		else
		{
			CCSprite* leftButton = CCSprite::create("cs_select.png",CCRect(leftButton_width,0,leftButton_width,leftButton_height));
			leftButton->setAnchorPoint(ccp(0,0));
			leftButton->setPosition(ccp(757,227));
			this->addChild(leftButton,6,tag_leftButton);

			CCSprite* rightButton = CCSprite::create("cs_cancle.png",CCRect(rightButton_width,0,rightButton_width,rightButton_height));
			rightButton->setAnchorPoint(ccp(0,0));
			rightButton->setPosition(ccp(992,227));
			this->addChild(rightButton,6,tag_rightButton);
		}
	}

	else if(charset == 3)
	{
		CCSprite* popUp = CCSprite::create("ex_livingdead.png");
		popUp->setAnchorPoint(ccp(0,0));
		popUp->setPosition(ccp(294,104));
		this->addChild(popUp,5,tag_popUp);

		if(global_livingDeadState == 0)
		{
			CCSprite* leftButton = CCSprite::create("cs_buy.png",CCRect(leftButton_width,0,leftButton_width,leftButton_height));
			leftButton->setAnchorPoint(ccp(0,0));
			leftButton->setPosition(ccp(757,227));
			this->addChild(leftButton,6,tag_leftButton);

			CCSprite* rightButton = CCSprite::create("cs_cancle.png",CCRect(rightButton_width,0,rightButton_width,rightButton_height));
			rightButton->setAnchorPoint(ccp(0,0));
			rightButton->setPosition(ccp(992,227));
			this->addChild(rightButton,6,tag_rightButton);
		}

		else
		{
			CCSprite* leftButton = CCSprite::create("cs_select.png",CCRect(leftButton_width,0,leftButton_width,leftButton_height));
			leftButton->setAnchorPoint(ccp(0,0));
			leftButton->setPosition(ccp(757,227));
			this->addChild(leftButton,6,tag_leftButton);

			CCSprite* rightButton = CCSprite::create("cs_cancle.png",CCRect(rightButton_width,0,rightButton_width,rightButton_height));
			rightButton->setAnchorPoint(ccp(0,0));
			rightButton->setPosition(ccp(992,227));
			this->addChild(rightButton,6,tag_rightButton);
		}
	}

}

void CharacterSelectScene::changingCharWhenPopClosed()
{
	if(global_subwayState == 1 && m_pressedCharNumber !=0)
	{
		CCSprite* subway = (CCSprite*)this->getChildByTag(tag_subway);
		subway->setTextureRect(CCRect(subway_width*2,0,subway_width,subway_height));
	}

	if(global_ringState == 1 && m_pressedCharNumber !=1)
	{
		CCSprite* ring = (CCSprite*)this->getChildByTag(tag_ring);
		ring->setTextureRect(CCRect(ring_width*2,0,ring_width,ring_height));
	}

	if(global_pinokState == 1 && m_pressedCharNumber !=2)
	{
		CCSprite* pinok = (CCSprite*)this->getChildByTag(tag_pinok);
		pinok->setTextureRect(CCRect(pinok_width*2,0,pinok_width,pinok_height));
	}

	if(global_livingDeadState == 1 && m_pressedCharNumber !=3)
	{
		CCSprite* livingDead = (CCSprite*)this->getChildByTag(tag_livingDead);
		livingDead->setTextureRect(CCRect(livingDead_width*2,0,livingDead_width,livingDead_height));
	}
}