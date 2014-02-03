#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainmenuScene.h"
#include "GameScene.h"
#include "global.h"

using namespace cocos2d;

class GameSelectScene : public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	CCSprite* m_stage[4];
	CCSprite* m_stageSelect[4];
	CCPoint m_touchBegin;
	CCPoint m_touchEnd;
	CCPoint m_moveVector;
	int m_scrollSpeed;

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject* pSender);
	void scrollSprite();

	virtual void ccTouchesBegan(CCSet* touches,CCEvent* event);
	virtual void ccTouchesEnded(CCSet* touches,CCEvent* event);
	CREATE_FUNC(GameSelectScene);
};