//
//  animation.hpp
//  areks
//
//  Created by inkooboo on 8/24/12.
//
//

#ifndef __areks__animation__
#define __areks__animation__

# include "defs.hpp"

# include <string>

# include <json/value.h>

class Animation
{
public:
    Animation(const char *name, cc::CCNode *node);

    void start(const char *action_name)
    {
        
    }
    
private:
    Json::Value m_descr;
    cc::CCNode *m_node;
};

#endif /* defined(__areks__animation__) */
