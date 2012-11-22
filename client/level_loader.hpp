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
# include "primitives.hpp"

# include "defs.hpp"

class LevelLoader : public subsystem_t
{
    DEFINE_LOGGER(LevelLoader);
    
    virtual void start() override;
    virtual void stop() override;
    
public:
    LevelLoader();
    
    void loadLevel(const char *level_name);
};




#endif /* defined(__areks__level_manager__) */
