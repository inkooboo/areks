#include "View.hpp"

void View::start()
{
    using namespace cocos2d;

    // run scene
    cc::CCDirector::sharedDirector()->runWithScene(_scene);
    
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
                                        menu_selector(View::menuExit) );

    pMenuItem->setPosition( ccp(m_size.width - 27, 28) );

    cc::CCMenu* menu = cc::CCMenu::create(pMenuItem, NULL);
    menu->setPosition( cc::CCPointZero );
    menu->setVisible(true);
    _mainLayer->addChild(menu, 1);
}

void View::stop()
{ 
    cc::CCObject::release();
}

View::View()
{
    _scene = cc::CCScene::create();
    _mainLayer = cc::CCLayer::create();
    _scene->addChild( _mainLayer );
}

void View::menuExit(cocos2d::CCObject* pSender)
{
    cc::CCDirector::sharedDirector()->end();
}