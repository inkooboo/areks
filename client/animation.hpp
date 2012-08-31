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

# include <loop.hpp>

# include <json/value.h>

# include <string>
# include <map>
# include <functional>

class Animation
{
    typedef std::map<std::string, cc::CCActionInterval *> AnimationsMap;
public:
    Animation(const char *name);
    ~Animation();

    cc::CCSprite *sprite();
    
    void animate(const std::string &name, LazyFunction on_animation_loop_end);
    
private:
    Json::Value m_descr;
    cc::CCSprite *m_sprite;
    cc::CCAction *m_cur_action;
    
    AnimationsMap m_animations;
};

#endif /* defined(__areks__animation__) */
