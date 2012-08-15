#ifndef _AREKS_ACTION_HANDLER_HPP_
#define _AREKS_ACTION_HANDLER_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <map>
# include <functional>

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

    
    struct Touch
    {
        cc::CCPoint begin;
        cc::CCPoint previous;
        std::function<void(cc::CCPoint &from, cc::CCPoint &to)> on_move;
        std::function<void(cc::CCPoint &begin, cc::CCPoint &end)> on_end;
    };
    
    std::map<int,Touch> m_touches;
};

#endif