#include "action_handler.hpp"

#include "master.hpp"

#include "level_manager/lm_view.hpp"
#include "level_manager/tool_manager.hpp"
#include "player.hpp"

#include "physics.hpp"
#include "objects/base_object.hpp"
#include "objects/player/body.hpp"
#include "objects/ball.hpp"

void ActionHandler::start()
{
    enable();
}

void ActionHandler::stop()
{
    disable();
}

ActionHandler::ActionHandler()
{
}

void ActionHandler::enable()
{
    cc::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
void ActionHandler::disable()
{
    cc::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

cc::CCPoint invert_y_coord(cc::CCPoint pos)
{
    pos.y = cc::CCDirector::sharedDirector()->getWinSize().height - pos.y;
    return pos;
}

//touches handle
bool ActionHandler::ccTouchBegan (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    cc::CCPoint location = invert_y_coord(pTouch->locationInView());
    int id = pTouch->getID();
    
    TouchPtr touch = std::make_shared<Touch>();
    touch->begin = location;
    touch->from = location;

    LMView &view = static_cast<LMView &>(master_t::subsystem<View>());

    // determine touch type and init touch handlers
    if (m_touches.size() == 0)
    {
        // 1. first scale touch OR
        // 2. possible view move touch OR
        
        //auto ball = objects::Ball::create(view.toWorldCoordinates(touch->begin));
        
		touch->on_move = std::bind(&LMView::onTouchMove, &view, std::placeholders::_1);
    }
    
    if (m_touches.size() == 1)
    {
        //scale second touch
        TouchPtr first_touch = m_touches.begin()->second;
        first_touch->on_move = std::function<void(TouchPtr &touch)>(); // disable movement
        first_touch->on_end = std::bind(&LMView::onTouchEnd, &view, first_touch);
        touch->on_end = std::bind(&LMView::onTouchEnd, &view, std::placeholders::_1);
        touch->on_move = std::bind(&LMView::onTouchScale, &view, first_touch, std::placeholders::_1);
    }
    
    m_touches[id] = touch;
    
    return true;
}

void ActionHandler::ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    TouchPtr &touch = m_touches[pTouch->getID()];

    touch->to = invert_y_coord(pTouch->locationInView());

    if (touch->on_move)
    {
        touch->on_move(touch);
    }

    touch->from = touch->to;
}

void ActionHandler::ccTouchEnded (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    int id = pTouch->getID();
    
    TouchPtr &touch = m_touches[id];
    
    touch->end = invert_y_coord(pTouch->locationInView());
    
    if (touch->on_end)
    {
        touch->on_end(touch);
    }
    
    touch->ended = true;
    
    m_touches.erase(id);
}

void ActionHandler::ccTouchCancelled (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    ccTouchEnded(pTouch, pEvent);
}