#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

class LoginScene : public cocos2d::CCLayerColor,public cocos2d::CCIMEDelegate
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject* pSender);

	void callBackLogo(CCNode* sender);

	virtual void ccTouchesBegan(CCSet* touches,CCEvent* event);
	virtual void ccTouchesEnded(CCSet* touches,CCEvent* event);

	void keyboardWillShow(CCIMEKeyboardNotificationInfo & Info);
	void keyboardWillHide(CCIMEKeyboardNotificationInfo & Info);
	CREATE_FUNC(LoginScene);
};