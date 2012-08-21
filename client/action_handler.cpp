#include "action_handler.hpp"
#include "view.hpp"
#include "master.hpp"
#include "objects/ball.hpp"

void ActionHandler::start()
{
    this->enable();
}

void ActionHandler::stop()
{
    this->disable();
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

//touches handle
bool ActionHandler::ccTouchBegan (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    cc::CCPoint location = pTouch->locationInView();
    int id = pTouch->getID();
    
    TouchPtr touch = std::make_shared<Touch>();
    touch->begin = location;
    touch->from = location;

    View &view = master_t::subsystem<View>();

    // determine touch type and init touch handlers
    if (m_touches.size() == 0)
    {
        // 1. first scale touch OR
        // 2. possible view move touch OR
        // 3. main hero selection
        touch->on_move = std::bind(&View::onTouchMove, &view, std::placeholders::_1);
    }
    
    if (m_touches.size() == 1)
    {
        //scale second touch
        TouchPtr first_touch = m_touches.begin()->second;
        first_touch->on_move = std::function<void(TouchPtr &touch)>(); // disable movement
        first_touch->on_end = std::bind(&View::onTouchEnd, &view, first_touch);
        touch->on_end = std::bind(&View::onTouchEnd, &view, std::placeholders::_1);
        touch->on_move = std::bind(&View::onTouchScale, &view, first_touch, std::placeholders::_1);
    }
    
    
    
    ///
    
    
    
    m_touches[id] = touch;
    
    return true;
}

void ActionHandler::ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    TouchPtr &touch = m_touches[pTouch->getID()];

    touch->to = pTouch->locationInView();

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
    
    touch->end = pTouch->locationInView();
    
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