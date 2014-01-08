#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "global.h"
#include "GameScene.h"
#include "MainmenuScene.h"
#include "OptionScene.h"
#include "RankScene.h"
#include "StrategyOfficeScene.h"
#include "GameSelectScene.h"

using namespace cocos2d;

class MainmenuScene : public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject* pSender);

	virtual void ccTouchesBegan(CCSet* touches,CCEvent* event);
	virtual void ccTouchesEnded(CCSet* touches,CCEvent* event);
	CREATE_FUNC(MainmenuScene);
};