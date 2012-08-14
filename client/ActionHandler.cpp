#include "ActionHandler.hpp"
#include "View.hpp"
#include "master.hpp"

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
    
    Touch touch;
    touch.begin = location;
    touch.previous = location;
    // determine touch type and init touch handlers
    
    View *view = &master_t::subsystem<View>();
    
    touch.on_move = std::bind(&View::on_touch_move, view, std::placeholders::_1, std::placeholders::_2);
    
    ///
    
    
    
    m_touches[id] = touch;
    
    return true;
}

void ActionHandler::ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    cc::CCPoint to = pTouch->locationInView();
    int id = pTouch->getID();
    
    Touch &touch = m_touches[id];

    cc::CCPoint from = touch.previous;
    
    if (touch.on_move)
    {
        touch.on_move(from, to);
    }
}

void ActionHandler::ccTouchEnded (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    cc::CCPoint end = pTouch->locationInView();
    int id = pTouch->getID();
    
    Touch &touch = m_touches[id];
    
    if (touch.on_end)
    {
        touch.on_end(touch.begin, end);
    }
    
    m_touches.erase(id);
}

void ActionHandler::ccTouchCancelled (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    ccTouchEnded(pTouch, pEvent);
}