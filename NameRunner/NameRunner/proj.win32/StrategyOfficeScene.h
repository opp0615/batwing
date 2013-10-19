#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainmenuScene.h"
using namespace cocos2d;

class StrategyOfficeScene : public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject* pSender);

	virtual void ccTouchesBegan(CCSet* touches,CCEvent* event);
	virtual void ccTouchesEnded(CCSet* touches,CCEvent* event);
	CREATE_FUNC(StrategyOfficeScene);
};