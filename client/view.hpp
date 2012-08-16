#ifndef _AREKS_VIEW_HPP_
#define _AREKS_VIEW_HPP_

# include "defs.hpp"
# include "subsystem.hpp"
# include "primitives.hpp"

class View : public cc::CCObject, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;
    
public:
    View();

    void menuExit(cocos2d::CCObject* pSender);

    void on_touch_move(cc::CCPoint &from, cc::CCPoint &to);
    
    
    float pixel_scale() const;
    cc::CCPoint toScreenCoordinates(pr::Vec2 world_coord) const;
    pr::Vec2 toWorldCoordinates(cc::CCPoint screen_coord) const;
    float worldToPixel(float world_size) const;
    float pixelToScreen(float pixel_size) const;
    float screenToPixel(float screen_size) const;
    float pixelToWorld(float pixel_size) const;
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
    
    pr::Vec2 m_cur_positon;
};

#endif