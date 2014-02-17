#include "loginScene.h"
#include "MainmenuScene.h"

CCScene* LoginScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        LoginScene *layer = LoginScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool LoginScene::init()
{
	if ( CCLayer::init() )
	{

		if (! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}

			

			CCSprite* logo = CCSprite::create("loding.png");
			logo->setAnchorPoint(ccp(0,0));
			logo->setPosition(ccp(0,0));

			this->addChild(logo);

			CCFadeIn *fadeIn = CCFadeIn::create(1);
			CCFadeOut* fadeOut = CCFadeOut::create(2);

			CCAction* actions = CCSequence::create(fadeIn,fadeOut,CCCallFuncN::create(this,callfuncN_selector(LoginScene::callBackLogo)),NULL);

			logo->runAction(actions);
	}
	return true;
}

void LoginScene::ccTouchesBegan(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
    CCTextFieldTTF *textfield = (CCTextFieldTTF *)this->getChildByTag(100);
	CCRect rect = textfield->boundingBox();



	if(rect.containsPoint(location))
	{
		textfield->attachWithIME();
	}

	CCScene *pScene = MainmenuScene::scene();
	CCTransitionScene* pTran = CCTransitionFade::create(1.0f, pScene);
	CCDirector::sharedDirector()->replaceScene(pTran);



}


void LoginScene::ccTouchesEnded(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
}

void LoginScene::callBackLogo(CCNode* sender)
{
	this->removeChild(sender);

	this->setTouchEnabled(true);

	CCSprite* background = CCSprite::create("StartImage_logo.png");
	background->setAnchorPoint(ccp(0,0));
	background->setPosition(ccp(0,0));
	this->addChild(background,0);

	/*
	CCSprite* logIn = CCSprite::create("login2.png");
	logIn->setAnchorPoint(ccp(0,0));
	logIn->setPosition(ccp(378,168));
	this->addChild(logIn,1);
	*/
	CCTextFieldTTF * textfield = CCTextFieldTTF::textFieldWithPlaceHolder("",CCSize(270,64),kCCTextAlignmentCenter,"Arial",20);
	textfield->setAnchorPoint(ccp(0,0));
	textfield->setPosition(ccp(378+190,168+190));
	this->addChild(textfield,2,100);
	
	/*
	CCLabelTTF* label = CCLabelTTF::create("","",50);
	label->setAnchorPoint(ccp(0,0));
	label->setPosition(ccp(378+190,168+190));
	this->addChild(label,2,200);
	*/
}

void LoginScene::keyboardWillShow(CCIMEKeyboardNotificationInfo & Info)
{
	CCTextFieldTTF* textfield = (CCTextFieldTTF*)this->getChildByTag(100);
	textfield->setString("");
}

void LoginScene::keyboardWillHide(CCIMEKeyboardNotificationInfo & Info)
{
	CCTextFieldTTF* textfield = (CCTextFieldTTF*)this->getChildByTag(100);

}