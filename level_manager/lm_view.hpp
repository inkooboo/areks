//
//  lm_view.hpp
//  level_manager
//
//  Created by inkooboo on 11/22/12.
//
//

#ifndef level_manager_view_traits_hpp
#define level_manager_view_traits_hpp

#include "level_manager/action_handler.hpp"
#include "level_manager/app_delegate.h"
#include "view.hpp"

struct LMView : public View
{
    virtual void start() override
    {
        View::start();
        m_in_touch = false;
    }
    
    virtual void menuExit(cc::CCObject*) override
    {
        master_t::subsystem<AppDelegate>().end_application();
    }
    
    virtual void menuTest(cc::CCObject*) override
    {
        
    }

    virtual void manageCameraPositionAndScale(float t) override
    {
        if (m_in_touch)
        {
            return;
        }
//        static const float timed_rescale_speed = .25;
//
//        if (m_view_scale > m_default_view_scale)
//        {
//            m_view_scale -= t * timed_rescale_speed;
//            if (m_view_scale < m_default_view_scale)
//            {
//                m_view_scale = m_default_view_scale;
//            }
//        }
//        else if (m_view_scale < m_default_view_scale)
//        {
//            m_view_scale += t * timed_rescale_speed;
//            if (m_view_scale > m_default_view_scale)
//            {
//                m_view_scale = m_default_view_scale;
//            }
//        }
        
        validateScale();
        validatePosition();
    }
    
    void onTouchMove(ActionHandler::TouchPtr &touch)
    {
        moveViewBy(touch->to.x - touch->from.x, touch->to.y - touch->from.y);
    }
    
    void onTouchScale(ActionHandler::TouchPtr &touch1, ActionHandler::TouchPtr &touch2)
    {
        m_in_touch = true;
        float dx1 = touch1->from.x - touch2->from.x;
        float dy1 = touch1->from.y - touch2->from.y;
        float distance1 = sqrt(dx1 * dx1 + dy1 * dy1);
        
        float dx2 = touch1->to.x - touch2->to.x;
        float dy2 = touch1->to.y - touch2->to.y;
        float distance2 = sqrt(dx2 * dx2 + dy2 * dy2);
        
        float d = distance2 - distance1;
        
        float touch_scale_speed = m_default_view_scale / 100;
        
        m_view_scale += d * touch_scale_speed;
        validateScale();
        validatePosition();
    }
    
    void onTouchEnd(ActionHandler::TouchPtr &touch)
    {
        m_in_touch = false;
    }

    bool m_in_touch;
};

#endif
