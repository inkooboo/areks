#include "View.hpp"
#include "master.hpp"
#include "AppDelegate.h"
#include "Physics.hpp"

#include <cassert>
#include <algorithm>

void View::start()
{
    using namespace cocos2d;

    // run scene
    cc::CCDirector::sharedDirector()->runWithScene(_scene);
    
    cc::CCSize m_size = cc::CCDirector::sharedDirector()->getWinSize();
    b2Vec2 world_size = master_t::subsystem<Physics>().worldSize();

    cc::CCSprite *background = cc::CCSprite::create("HelloWorld.png");
    cc::CCSize bg_size = background->getContentSize();
    
    float x_world_scale = bg_size.width / world_size.x;
    float y_world_scale = bg_size.height / world_size.y;
    
    assert(x_world_scale == y_world_scale && "background and world should be with corresponding proportions");

    _world_scale = x_world_scale;
    
    float x_view_scale = m_size.width / bg_size.width;
    float y_view_scale = m_size.height / bg_size.height;
    
    //float
    
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
}

View::View()
{
    _scene = cc::CCScene::create();
    _mainLayer = cc::CCLayer::create();
    _scene->addChild( _mainLayer );
}

void View::menuExit(cocos2d::CCObject* pSender)
{
    master_t::subsystem<AppDelegate>().end_application();
}

float View::toPixel(float world_size)
{
    return world_size * _world_scale;
}

float View::toWorld(float pixel_size)
{
    return pixel_size / _world_scale;
}

