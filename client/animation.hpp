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
# include <map>
# include <json/value.h>

class Animation
{
    typedef std::map<std::string, cc::CCActionInterval *> AnimationsMap;
public:
    Animation(const char *name);
    ~Animation();

    cc::CCSprite *sprite();
    
    void animate(const std::string &name);
    
private:
    Json::Value m_descr;
    cc::CCSprite *m_sprite;
    
    AnimationsMap m_animations;
};

#endif /* defined(__areks__animation__) */
