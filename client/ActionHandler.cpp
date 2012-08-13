#include "ActionHandler.hpp"

void ActionHandler::start()
{
    this->Enable();        
}

void ActionHandler::stop()
{
    this->Disable();
}

ActionHandler::ActionHandler()
{
}

void ActionHandler::Enable()
{
    cc::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
void ActionHandler::Disable()
{
    cc::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

//touches handle
bool ActionHandler::ccTouchBegan (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
    return true;
}

void ActionHandler::ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
}

void ActionHandler::ccTouchEnded (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
}

void ActionHandler::ccTouchCancelled (cc::CCTouch *pTouch, cc::CCEvent *pEvent)
{
}