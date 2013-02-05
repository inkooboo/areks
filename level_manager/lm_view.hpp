//
//  lm_view.hpp
//  level_manager
//
//  Created by inkooboo on 11/22/12.
//
//

#ifndef level_manager_view_traits_hpp
#define level_manager_view_traits_hpp

#include "defs.hpp"
#include "level_manager/action_handler.hpp"
#include "level_manager/app_delegate.h"
#include "resource_utils.hpp"
#include "view.hpp"

#include "level_manager/tool_manager.hpp"
#include "level_manager/tools.hpp"

struct LMView : public cc::CCObject, public View
{
    virtual void start() override
    {
        View::start();
        m_in_touch = false;

        using namespace cocos2d;
        
        cc::CCMenuItemImage *pClose = cc::CCMenuItemImage::create(
                                                                  res::picture("CloseNormal").c_str(),
                                                                  res::picture("CloseSelected").c_str(),
                                                                  this,
                                                                  menu_selector(LMView::menuExit) );
        
        pClose->setPosition( ccp(m_size.width - 27, m_size.height - 28) );
        
//        cc::CCMenuItemImage *pReload = cc::CCMenuItemImage::create(
//                                                                   res::picture("shesterenka").c_str(),
//                                                                   res::picture("shesterenka_p").c_str(),
//                                                                   this,
//                                                                   menu_selector(LMView::menuTest) );
//        
//        pReload->setPosition( ccp(m_size.width - 27, 28) );
        
        cc::CCMenuItemImage *platfrom_tool = cc::CCMenuItemImage::create(
                                                                   res::picture("platform_tool").c_str(),
                                                                   res::picture("platform_tool").c_str(),
                                                                   this,
                                                                   menu_selector(LMView::menuPlatformTool) );

        platfrom_tool->setPosition( ccp(28, m_size.height - 27) );

        
        createGameLayerMenu(cc::CCArray::create(pClose, platfrom_tool, NULL));
    }
    
    void menuExit(cc::CCObject*)
    {
        master_t::subsystem<AppDelegate>().end_application();
    }
    
//    void menuTest(cc::CCObject*)
//    {
//        
//    }

    void menuPlatformTool(cc::CCObject*)
    {
        master_t::subsystem<ToolManager>().resetcurrentTool<PlatformTool>();
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
