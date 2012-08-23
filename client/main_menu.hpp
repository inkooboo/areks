//
//  main_menu.hpp
//  areks
//
//  Created by inkooboo on 8/23/12.
//
//

#ifndef __areks__main_menu__
#define __areks__main_menu__

# include "defs.hpp"
# include "subsystem.hpp"
# include "primitives.hpp"

class MainMenu : public cc::CCObject, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;
    
public:
    MainMenu();
    ~MainMenu();
    
    cc::CCScene * scene();
    
    void onStart(cc::CCObject *);
    void onExit(cc::CCObject *);
    
private:
    cc::CCScene *m_scene;
	cc::CCMenu *m_menu;
};


#endif /* defined(__areks__main_menu__) */
