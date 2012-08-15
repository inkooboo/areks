//
//  level_manager.h
//  areks
//
//  Created by inkooboo on 8/15/12.
//
//

#ifndef __areks__level_manager__
#define __areks__level_manager__

# include "subsystem.hpp"

class LevelManager : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;
    
public:
    LevelManager();

    const char * backgroundName();
};




#endif /* defined(__areks__level_manager__) */
