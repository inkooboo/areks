#ifndef _AREKS_ACTION_HANDLER_HPP_
#define _AREKS_ACTION_HANDLER_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

class ActionHandler : public cc::CCObject, public cc::CCTargetedTouchDelegate, public subsystem_t
{
    virtual void start();
    virtual void stop();

public:
    ActionHandler();

    void Enable();
    void Disable();

private:
    //touches handle
    virtual bool ccTouchBegan (cc::CCTouch *pTouch, cc::CCEvent *pEvent);
    virtual void ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent);
    virtual void ccTouchEnded (cc::CCTouch *pTouch, cc::CCEvent *pEvent);
    virtual void ccTouchCancelled (cc::CCTouch *pTouch, cc::CCEvent *pEvent);
};

#endif