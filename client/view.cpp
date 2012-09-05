#include "view.hpp"

#include "master.hpp"
#include "physics.hpp"
#include "resource_utils.hpp"
#include "game_logic.hpp"
#include "main_menu.hpp"

#include "effects/flying_text.hpp"

#include <algorithm>

void View::start()
{
    m_game_layer = cc::CCLayer::create();
    
    createGameLayerMenu();

    m_scene->addChild(m_game_layer);

    m_in_touch = false;
}

void View::stop()
{
    m_scene->removeChild(m_game_layer, true);
}

View::View()
{
    m_scene = new cc::CCScene();
    m_scene->init();
    m_size = cc::CCDirector::sharedDirector()->getWinSize();
}

View::~View()
{
}

cc::CCScene * View::scene()
{
    return m_scene;
}

void View::reload(cc::CCSize bg_size, pr::Vec2 world_size)
{
    stop();
    start();
    
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
    
    m_half_screen_in_world_size.x = pixelToWorld(screenToPixel(m_size.width)) / 2;;
    m_half_screen_in_world_size.y = pixelToWorld(screenToPixel(m_size.height)) / 2;
    
    m_cur_positon = pr::Vec2(world_size.x / 2 , world_size.y / 2);
    
}

void View::createGameLayerMenu()
{
    using namespace cocos2d;
    
    cc::CCMenuItemImage *pClose = cc::CCMenuItemImage::create(
                                                            res::picture("CloseNormal").c_str(),
                                                            res::picture("CloseSelected").c_str(),
                                                            this,
                                                            menu_selector(View::menuExit) );
    
    pClose->setPosition( ccp(m_size.width - 27, m_size.height - 28) );
    
    cc::CCMenuItemImage *pReload = cc::CCMenuItemImage::create(
                                                               res::picture("shesterenka").c_str(),
                                                               res::picture("shesterenka_p").c_str(),
                                                               this,
                                                               menu_selector(View::menuTest) );
    
    pReload->setPosition( ccp(m_size.width - 27, 28) );

    cc::CCMenu* menu = cc::CCMenu::create(pClose, pReload, NULL);
    menu->setPosition( cc::CCPointZero );
    menu->setVisible(true);
    m_game_layer->addChild(menu, 100);
}


void View::menuExit(cocos2d::CCObject*)
{
    master_t::subsystem<GameLogic>().loadScene(master_t::subsystem<MainMenu>().scene());
}

void View::menuTest(cocos2d::CCObject*s)
{
    /// test sound fx. Remove it.
#ifndef NO_SOUND
    master_t::subsystem<cd::SimpleAudioEngine>().playEffect(res::sound_effect("046").c_str());
#endif
    ///
    
    /// test effects. Remove it.
    pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();
    world_size *= .5f;
    
    effects::FlyingText::create(world_size, m_game_layer, "Test Text", 14, cc::ccc3(190, 255, 190), 5.f);
    ///
}

float View::pixelScale() const
{
    return m_view_scale;
}

cc::CCPoint View::toScreenCoordinates(pr::Vec2 world_coord) const
{
    world_coord += m_half_screen_in_world_size;
    world_coord -= m_cur_positon;
    return cc::CCPoint(pixelToScreen(worldToPixel(world_coord.x)), /*m_size.height - */pixelToScreen(worldToPixel(world_coord.y)));
}

pr::Vec2 View::toWorldCoordinates(cc::CCPoint screen_coord) const
{
    pr::Vec2 world_coord = pr::Vec2(pixelToWorld(screenToPixel(screen_coord.x)), pixelToWorld(screenToPixel(/*m_size.height - */screen_coord.y)));
    world_coord += m_cur_positon;
    world_coord -= m_half_screen_in_world_size;
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
    return m_game_layer;
}

void View::onTouchEnd(ActionHandler::TouchPtr &touch)
{
    m_in_touch = false;
}

void View::onTouchMove(ActionHandler::TouchPtr &touch)
{
    moveView(touch->to.x - touch->from.x, touch->to.y - touch->from.y);
}

void View::onTouchScale(ActionHandler::TouchPtr &touch1, ActionHandler::TouchPtr &touch2)
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
    validateScale();
    moveView(0,0);
}

void View::onRescaleTick(float t)
{
    if (m_in_touch)
    {
        return;
    }
    
    static const float timed_rescale_speed = .25;
 
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

    validateScale();
    moveView(0,0);
}

pr::Vec2 View::currentCameraPosition() const
{
    return m_cur_positon;
}

void View::validateScale()
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
    m_half_screen_in_world_size.x = pixelToWorld(screenToPixel(m_size.width)) / 2;;
    m_half_screen_in_world_size.y = pixelToWorld(screenToPixel(m_size.height)) / 2;

    float x_margin = m_half_screen_in_world_size.x;
    float y_margin = m_half_screen_in_world_size.y;
    
    dx = -pixelToWorld(screenToPixel(dx));
    dy = -pixelToWorld(screenToPixel(dy));
    
    pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();
    
    m_cur_positon.x += dx;
    if (m_cur_positon.x < x_margin)
    {
        m_cur_positon.x = x_margin;
    }
    if (m_cur_positon.x > world_size.x - x_margin)
    {
        m_cur_positon.x = world_size.x - x_margin;
    }

    m_cur_positon.y += dy;
    if (m_cur_positon.y < y_margin)
    {
        m_cur_positon.y = y_margin;
    }
    if (m_cur_positon.y > world_size.y - y_margin)
    {
        m_cur_positon.y = world_size.y - y_margin;
    }
}

void View::addSprite(cc::CCNode *sprite, int z_order)
{
    m_game_layer->addChild( sprite, z_order );
}

void View::removeSprite(cc::CCNode *sprite)
{
    sprite->removeFromParentAndCleanup(true);
}

void View::drawSpriteHelper(cc::CCNode *sprite, pr::Vec2 position, float angle)
{
    const cc::CCPoint &prev_position = sprite->getPosition();
    cc::CCPoint cur_position = toScreenCoordinates(position);
    if (prev_position.x != cur_position.x || prev_position.y != cur_position.y)
    {
        sprite->setPosition(cur_position);
    }
    
    float prev_scale = sprite->getScale();
    float cur_scale = pixelScale();
    if (prev_scale != cur_scale)
    {
        sprite->setScale(cur_scale);
    }
    
    //rotation in Box2d - in radiance
    //rotation in cocos2d-x - in degrees
    float prev_angle = sprite->getRotation();
    float cur_angle = -angle * 180/b2_pi; //FIXME minus ??? are you sure?
    if (prev_angle != angle)
    {
        sprite->setRotation( cur_angle );
    }
}


