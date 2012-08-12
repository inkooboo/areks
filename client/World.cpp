#include "World.hpp"

void World::start()
{
    using namespace cocos2d;
    // run scene
    cc::CCDirector::sharedDirector()->runWithScene(this);

    _mainLayer = cc::CCLayer::create();
    
    cc::CCSize m_size = cc::CCDirector::sharedDirector()->getWinSize();
    cc::CCSprite *background = cc::CCSprite::create("HelloWorld.png");

    cc::CCSize bg_size = background->getContentSize();
    float bg_scale_x = m_size.width / bg_size.width;
    float bg_scale_y = m_size.height / bg_size.height;
    background->setScaleX(bg_scale_x);
    background->setScaleY(bg_scale_y);
    background->setPosition( ccp(m_size.width/2, m_size.height/2) );
    _mainLayer->addChild(background, 0);
    
    
    cc::CCMenuItemImage *pMenuItem = cc::CCMenuItemImage::create(
                                        "shesterenka.png",
                                        "shesterenka_p.png",
                                        this,
                                        menu_selector(World::menuOpenCallback) );

    pMenuItem->setPosition( ccp(m_size.width - 27, 28) );

    cc::CCMenu* menu = cc::CCMenu::create(pMenuItem, NULL);
    menu->setPosition( cc::CCPointZero );
    menu->setVisible(true);
    _mainLayer->addChild(menu, 1);

    cc::CCScene::addChild( _mainLayer );

    this->Enable();
}

void World::strop()
{
    this->Disable();
}
    
World::World()
{
    cc::CCScene::init();
    cc::CCScene::autorelease();
}

void World::Enable()
{
    //enable World loop
    cc::CCScene::schedule( schedule_selector(World::Loop), 1);

    //enable touch handle
    cc::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void World::Disable()
{
    using namespace cocos2d;
    cc::CCScene::unschedule( schedule_selector(World::Loop) );
    cc::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


void World::Loop(float t)
{
}

// a selector callback
void World::menuOpenCallback(cocos2d::CCObject* pSender)
{
    cc::CCDirector::sharedDirector()->end();
}

bool World::ccTouchBegan (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    return true;
}
void World::ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
}
void World::ccTouchEnded (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
}
void World::ccTouchCancelled (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
}