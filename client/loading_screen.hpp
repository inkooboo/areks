//
//  loading_screen.hpp
//  areks
//
//  Created by inkooboo on 8/23/12.
//
//

#ifndef __areks__loading_screen__
#define __areks__loading_screen__

# include "defs.hpp"
# include "subsystem.hpp"
# include "primitives.hpp"

class LoadingScreen : public cc::CCObject, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;
    
public:
    LoadingScreen();
    ~LoadingScreen();
    
    cc::CCScene * scene();
    
private:
    cc::CCScene *m_scene;
	cc::CCLayer *m_layer;
};

#endif /* defined(__areks__loading_screen__) */
