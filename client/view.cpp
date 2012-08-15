#include "view.hpp"
#include "master.hpp"
#include "app_delegate.h"
#include "physics.hpp"
#include "level_manager.hpp"

#include <cassert>
#include <algorithm>

void View::start()
{
    using namespace cocos2d;
    
    // run scene
    cc::CCDirector::sharedDirector()->runWithScene(m_scene);
    
    m_size = cc::CCDirector::sharedDirector()->getWinSize();
    pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();

    cc::CCSprite *background_img = cc::CCSprite::create(master_t::subsystem<LevelManager>().backgroundName());
    cc::CCSize bg_size = background_img->getContentSize();
    background_img->release();
    
    float x_world_scale = bg_size.width / world_size.x;
    float y_world_scale = bg_size.height / world_size.y;
    
    assert(x_world_scale == y_world_scale && "background and world should be with corresponding proportions");

    m_world_scale = x_world_scale;
    
    float x_view_scale = m_size.width / bg_size.width;
    float y_view_scale = m_size.height / bg_size.height;
    
    float max_view_scale = std::max(x_view_scale, y_view_scale);
    
    if (max_view_scale <= 1.f)
    {
        m_default_view_scale = 1.f;
    }
    else
    {
        m_default_view_scale = max_view_scale;
    }
    
    m_view_scale = m_default_view_scale;
    
    m_x_margin = toWorld(m_size.width / 2);
    m_y_margin = toWorld(m_size.height / 2);
    
    m_cur_positon = pr::Vec2(0, 0);
    
    cc::CCMenuItemImage *pMenuItem = cc::CCMenuItemImage::create(
                                        "shesterenka.png",
                                        "shesterenka_p.png",
                                        this,
                                        menu_selector(View::menuExit) );

    pMenuItem->setPosition( ccp(m_size.width - 27, 28) );

    cc::CCMenu* menu = cc::CCMenu::create(pMenuItem, NULL);
    menu->setPosition( cc::CCPointZero );
    menu->setVisible(true);
    m_mainLayer->addChild(menu, 1);
}

void View::stop()
{ 
}

View::View()
{
    m_scene = cc::CCScene::create();
    m_mainLayer = cc::CCLayer::create();
    m_scene->addChild( m_mainLayer );
}

void View::menuExit(cocos2d::CCObject* pSender)
{
    master_t::subsystem<AppDelegate>().end_application();
}

float View::pixel_scale() const
{
    return m_view_scale;
}

cc::CCPoint View::toScreenCoordinates(pr::Vec2 world_coord) const
{
    world_coord -= m_cur_positon;
    return cc::CCPoint(toPixel(world_coord.x), toPixel(world_coord.y));
}

pr::Vec2 View::toWorldCoordinates(cc::CCPoint screen_coord) const
{
    pr::Vec2 world_coord = pr::Vec2(toWorld(screen_coord.x), toWorld(screen_coord.y));
    world_coord += m_cur_positon;
    return world_coord;
}


float View::toPixel(float world_size) const
{
    return world_size * m_world_scale * m_view_scale;
}


float View::toWorld(float screen_size) const
{
    return screen_size / (m_world_scale * m_view_scale);
}


cc::CCLayer * View::gameLayer()
{
    return m_mainLayer;
}

void View::on_touch_move(cc::CCPoint &from, cc::CCPoint &to)
{
    moveView(to.x - from.x, to.y - from.y);
}

void View::moveView(float dx, float dy)
{
    dx = -toWorld(dx);
    dy = toWorld(dy);
    
    pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();

    m_cur_positon.x += dx;
    if (m_cur_positon.x < 0)
    {
        m_cur_positon.x = 0;
    }
    if (m_cur_positon.x > world_size.x - m_x_margin * 2)
    {
        m_cur_positon.x = world_size.x - m_x_margin * 2;
    }

    m_cur_positon.y += dy;
    if (m_cur_positon.y < 0)
    {
        m_cur_positon.y = 0;
    }
    if (m_cur_positon.y > world_size.y - m_y_margin * 2)
    {
        m_cur_positon.y = world_size.y - m_y_margin * 2;
    }
}
