//
//  tools.cpp
//  level_manager
//
//  Created by inkooboo on 2/5/13.
//
//

#include "level_manager/tools.hpp"
#include "level_manager/tool_manager.hpp"

#include "master.hpp"

void Tool::on_click(ActionHandler::TouchPtr &touch)
{
    pr::Vec2 pos = master_t::subsystem<View>().toWorldCoordinates(touch->begin);
    if (pos == m_prev_click)
    {
        on_dbl_click(pos);
    }
    else
    {
        on_one_click(pos);
    }
    m_prev_click = pos;
}

void PlatformTool::on_one_click(const pr::Vec2 &pos)
{
    m_points.push_back(pos);
}

void PlatformTool::on_dbl_click(const pr::Vec2 &pos)
{
    // create platform
    
    
    master_t::subsystem<ToolManager>().dropTool();
}
