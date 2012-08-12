#ifndef _WORLD_HPP_
#define _WORLD_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <Box2D/Box2D.h>

//managed subsystem World
class World : public subsystem_t, public cc::CCScene, public cc::CCTargetedTouchDelegate
{
public:
    //subsytems methods
    virtual void start();
    virtual void strop();
    
    World();

    // Enable/disable world loop, touches handle
    void Enable();
    void Disable();

    //World loop
    void Loop(float t);

    // a selector callback
    void menuOpenCallback(cocos2d::CCObject* pSender);

    //touches handle
    virtual bool ccTouchBegan (cc::CCTouch *pTouch, cc::CCEvent *pEvent);
    virtual void ccTouchMoved (cc::CCTouch *pTouch, cc::CCEvent *pEvent);
    virtual void ccTouchEnded (cc::CCTouch *pTouch, cc::CCEvent *pEvent);
    virtual void ccTouchCancelled (cc::CCTouch *pTouch, cc::CCEvent *pEvent);

private:
    cc::CCLayer* _mainLayer;
};

#endif