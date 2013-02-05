//
//  tools.hpp
//  level_manager
//
//  Created by inkooboo on 2/5/13.
//
//

#ifndef level_manager_tools_hpp
#define level_manager_tools_hpp

# include "defs.hpp"
# include "primitives.hpp"
# include "level_manager/action_handler.hpp"
# include "view.hpp"
# include "master.hpp"

# include <list>

struct Tool
{
    virtual ~Tool() {}
    
    void on_click(ActionHandler::TouchPtr &touch);
    
    virtual void on_one_click(const pr::Vec2 &pos) = 0;
    virtual void on_dbl_click(const pr::Vec2 &pos) = 0;

protected:
    pr::Vec2 m_prev_click;
};


struct PlatformTool : public Tool
{
    void on_one_click(const pr::Vec2 &pos) override;
    void on_dbl_click(const pr::Vec2 &pos) override;
private:
    std::list<pr::Vec2> m_points;
};

#endif
