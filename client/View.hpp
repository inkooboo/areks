#ifndef _AREKS_VIEW_HPP_
#define _AREKS_VIEW_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

class View : public cc::CCObject, public subsystem_t
{
    virtual void start();
    virtual void stop();
    
public:
    View();

    void menuExit(cocos2d::CCObject* pSender);

    
    float toPixel(float world_size);
    float toWorld(float pixel_size);
    
private:
    cc::CCScene* _scene;
    cc::CCLayer* _mainLayer;
    
    float _view_scale;
    float _world_scale;
};

#endif