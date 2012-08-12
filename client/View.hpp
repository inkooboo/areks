#ifndef _AREKS_VIEW_HPP_
#define _AREKS_VIEW_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

class View : public cc::CCObject, public subsystem_t
{
public:
    virtual void start();
    virtual void stop();

    View();

    void menuExit(cocos2d::CCObject* pSender);

private:
    cc::CCScene* _scene;
    cc::CCLayer* _mainLayer;
};

#endif