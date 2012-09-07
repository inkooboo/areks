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
        std::string ret("pictures/");
        ret += name;
        
        //TODO: for real good devices load HD resources
        
        ret += ".png";
        
        return ret;
    }

    std::string animation_frame(const char *path)
    {
        std::string ret(path);

        //TODO: for real good devices load HD resources
        
        ret += ".png";
        
        return ret;
    }

    std::string animation_base_path(const char *name)
    {
        std::string ret("animations/");
        ret += name;
        
        //TODO: for real good devices load HD resources
        
        ret += "/";
        
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
    
    std::string level_description(const char *name)
    {
        std::string ret("levels/");
        ret += name;
        ret += ".json";
        return ret;
    }
    
    
    std::string load_file_content(const std::string &file_name)
    {
        const char *full_path = cc::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(file_name.c_str());
        unsigned char *data = 0;
        unsigned long size = 0;
        data = cc::CCFileUtils::sharedFileUtils()->getFileData(full_path, "r", &size);
        
        std::string ret;
        if (data && size)
        {
            ret.assign((char *)data, size);
        }
        
        return ret;
    }
}
