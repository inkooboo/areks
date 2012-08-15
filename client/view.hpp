#ifndef _AREKS_VIEW_HPP_
#define _AREKS_VIEW_HPP_

# include "defs.hpp"
# include "subsystem.hpp"
# include "physics.hpp"

class View : public cc::CCObject, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;
    
public:
    View();

    void menuExit(cocos2d::CCObject* pSender);

    void on_touch_move(cc::CCPoint &from, cc::CCPoint &to);
    
    
    cc::CCPoint toScreenCoordinates(b2Vec2 &world_coord) const;
    b2Vec2 toWorldCoordinates(cc::CCPoint screen_coord) const;
    float toPixel(float world_size) const;
    float toWorld(float screen_size) const;
    cc::CCLayer * gameLayer();
    
    void moveView(float dx, float dy);
    
private:
    cc::CCScene *m_scene;
    cc::CCLayer *m_mainLayer;
    
    cc::CCSize m_size;
    
    float m_view_scale;
    float m_default_view_scale;
    float m_world_scale;
    float m_x_margin;
    float m_y_margin;
    
    b2Vec2 m_cur_positon;
};

#endif