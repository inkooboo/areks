#ifndef _AREKS_ACTION_HANDLER_HPP_
#define _AREKS_ACTION_HANDLER_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <map>
# include <functional>
# include <memory>

class ActionHandler : public cc::CCObject, public cc::CCTargetedTouchDelegate, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    struct Touch;
    typedef std::shared_ptr<Touch> TouchPtr;
    
    struct Touch
    {
        Touch() : ended(false) {}
        cc::CCPoint begin;
        cc::CCPoint from;
        cc::CCPoint to;
        cc::CCPoint end;
        std::function<void(TouchPtr &touch)> on_move;
        std::function<void(TouchPtr &touch)> on_end;
        bool ended;
    };
    
    ActionHandler();

    void enable();
    void disable();

private:
    //touches handle
    virtual bool ccTouchBegan (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
    virtual void ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
    virtual void ccTouchEnded (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;
    virtual void ccTouchCancelled (cc::CCTouch *pTouch, cc::CCEvent *pEvent) override;

    
    std::map<int,TouchPtr> m_touches;
};

#endif