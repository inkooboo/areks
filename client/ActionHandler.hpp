#ifndef _AREKS_ACTION_HANDLER_HPP_
#define _AREKS_ACTION_HANDLER_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

class ActionHandler : public cc::CCObject, public cc::CCTargetedTouchDelegate, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    ActionHandler();

    void Enable();
    void Disable();

private:
    //touches handle
    virtual bool ccTouchBegan (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
    virtual void ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
    virtual void ccTouchEnded (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
    virtual void ccTouchCancelled (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
};

#endif