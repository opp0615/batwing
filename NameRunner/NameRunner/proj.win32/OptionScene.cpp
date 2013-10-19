#include "OptionScene.h"


CCScene* OptionScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        OptionScene *layer = OptionScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool OptionScene::init()
{
	if ( CCLayer::init() )
	{

		if (! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}

			this->setTouchEnabled(true);
	}
	return true;
}

void OptionScene::ccTouchesBegan(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
}


void OptionScene::ccTouchesEnded(CCSet* touches,CCEvent* event)	
{
	CCTouch* touch = (CCTouch*)(touches ->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
}