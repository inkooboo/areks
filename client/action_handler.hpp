#ifndef _AREKS_ACTION_HANDLER_HPP_
#define _AREKS_ACTION_HANDLER_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <map>
# include <functional>
# include <memory>

#include "action_target.hpp"

class ActionHandler : public cc::CCObject, public cc::CCTargetedTouchDelegate, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:    
    ActionHandler();

    void enable();
    void disable();

private:
    //touches handle
    virtual bool ccTouchBegan (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
    virtual void ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
    virtual void ccTouchEnded (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
    virtual void ccTouchCancelled (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;

    
    std::map<int,action::TouchPtr> m_touches;
	std::vector<int> m_touches_ids;

	ActionTarget* _active_target;
};

#endif