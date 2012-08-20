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

    m_min_view_scale = std::max(x_view_scale, y_view_scale);
    m_max_view_scale = m_min_view_scale * 2;
    
    m_default_view_scale = (m_min_view_scale + m_max_view_scale) / 2;
    
    m_view_scale = m_default_view_scale;
    
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
    m_in_touch = false;
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
    return cc::CCPoint(pixelToScreen(worldToPixel(world_coord.x)), pixelToScreen(worldToPixel(world_coord.y)));
}

pr::Vec2 View::toWorldCoordinates(cc::CCPoint screen_coord) const
{
    pr::Vec2 world_coord = pr::Vec2(pixelToWorld(screenToPixel(screen_coord.x)), pixelToWorld(screenToPixel(m_size.height - screen_coord.y)));
    world_coord += m_cur_positon;
    return world_coord;
}


float View::worldToPixel(float world_size) const
{
    return world_size * m_world_scale;
}

float View::pixelToScreen(float pixel_size) const
{
    return pixel_size * m_view_scale;
}

float View::screenToPixel(float screen_size) const
{
    return screen_size / m_view_scale;
}

float View::pixelToWorld(float pixel_size) const
{
    return pixel_size / m_world_scale;
}

cc::CCLayer * View::gameLayer()
{
    return m_mainLayer;
}

void View::on_touch_end(ActionHandler::TouchPtr &touch)
{
    m_in_touch = false;
}

void View::on_touch_move(ActionHandler::TouchPtr &touch)
{
    moveView(touch->to.x - touch->from.x, touch->to.y - touch->from.y);
}

void View::on_touch_scale(ActionHandler::TouchPtr &touch1, ActionHandler::TouchPtr &touch2)
{
    m_in_touch = true;
    float dx1 = touch1->from.x - touch2->from.x;
    float dy1 = touch1->from.y - touch2->from.y;
    float distance1 = sqrt(dx1 * dx1 + dy1 * dy1);
    
    float dx2 = touch1->to.x - touch2->to.x;
    float dy2 = touch1->to.y - touch2->to.y;
    float distance2 = sqrt(dx2 * dx2 + dy2 * dy2);
    
    float d = distance2 - distance1;
    
    float touch_scale_speed = m_default_view_scale / 100;
    
    m_view_scale += d * touch_scale_speed;
    validate_scale();
    moveView(0,0);
}

void View::on_rescale_tick(float t)
{
    if (m_in_touch)
    {
        return;
    }
    
    static const float timed_rescale_speed = .5;
 
    if (m_view_scale > m_default_view_scale)
    {
        m_view_scale -= t * timed_rescale_speed;
        if (m_view_scale < m_default_view_scale)
        {
            m_view_scale = m_default_view_scale;
        }
    }
    else if (m_view_scale < m_default_view_scale)
    {
        m_view_scale += t * timed_rescale_speed;
        if (m_view_scale > m_default_view_scale)
        {
            m_view_scale = m_default_view_scale;
        }
    }

    validate_scale();
    moveView(0,0);
}

void View::validate_scale()
{
    if (m_view_scale < m_min_view_scale)
    {
        m_view_scale = m_min_view_scale;
    }
    if (m_view_scale > m_max_view_scale)
    {
        m_view_scale = m_max_view_scale;
    }
}

void View::moveView(float dx, float dy)
{

    float x_margin = pixelToWorld(screenToPixel(m_size.width));
    float y_margin = pixelToWorld(screenToPixel(m_size.height));
    
    dx = -pixelToWorld(screenToPixel(dx));
    dy = pixelToWorld(screenToPixel(dy));
    
    pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();

    m_cur_positon.x += dx;
    if (m_cur_positon.x < 0)
    {
        m_cur_positon.x = 0;
    }
    if (m_cur_positon.x > world_size.x - x_margin)
    {
        m_cur_positon.x = world_size.x - x_margin;
    }

    m_cur_positon.y += dy;
    if (m_cur_positon.y < 0)
    {
        m_cur_positon.y = 0;
    }
    if (m_cur_positon.y > world_size.y - y_margin)
    {
        m_cur_positon.y = world_size.y - y_margin;
    }
}
