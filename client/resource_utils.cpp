//
//  resource_utils.cpp
//  areks
//
//  Created by inkooboo on 8/21/12.
//
//

#include "resource_utils.hpp"

namespace res
{
    std::string picture(const char *name)
    {
        std::string ret(name);
        
        ret += ".png";
        
        return ret;
    }

    std::string sound_effect(const char *name)
    {
        std::string ret("sound_fx/");
        ret += name;
#ifdef _WINDOWS
        ret += ".wav";
#else
        ret += ".mp3";
#endif
        return ret;
    }


    std::string background_sound(const char *name)
    {
        std::string ret("bg_sound/");
        ret += name;
#ifdef _WINDOWS
        ret += ".wav";
#else
        ret += ".mp3";
#endif
        return ret;
    }
}
