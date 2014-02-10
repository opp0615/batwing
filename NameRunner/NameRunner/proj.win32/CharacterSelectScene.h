#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainmenuScene.h"
#include "StrategyOfficeScene.h"
using namespace cocos2d;

class CharacterSelectScene : public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	bool m_popUpState ;
	int m_pressedCharNumber;

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject* pSender);

	void charSelectPopUp(int charset);
	void changingCharWhenPopClosed();

	void subwayStateFinding(bool state);
	void ringStateFinding(bool state);
	void pinokStateFinding(bool state);
	void livingDeadStateFinding(bool state);

	virtual void ccTouchesBegan(CCSet* touches,CCEvent* event);
	virtual void ccTouchesEnded(CCSet* touches,CCEvent* event);
	CREATE_FUNC(CharacterSelectScene);
};