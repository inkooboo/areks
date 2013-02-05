//
//  tool_manager.hpp
//  level_manager
//
//  Created by inkooboo on 2/5/13.
//
//

#ifndef level_manager_tool_manager_hpp
#define level_manager_tool_manager_hpp

# include "defs.hpp"
# include "subsystem.hpp"
# include "tools.hpp"

# include <map>
# include <functional>
# include <memory>

class ToolManager
{
public:
    
    template <typename ToolType>
    void resetcurrentTool()
    {
        m_tool.reset(new ToolType);
    }
    
    void dropTool()
    {
        m_tool.reset();
    }
    
    bool hasTool() const
    {
        return !!m_tool;
    }
    
    std::shared_ptr<Tool> currentTool()
    {
        return m_tool;
    }
    
public:
    std::shared_ptr<Tool> m_tool;
};


#endif
