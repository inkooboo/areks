//
//  resource_utils.hpp
//  areks
//
//  Created by inkooboo on 8/21/12.
//
//

#ifndef __areks__resource_utils__
#define __areks__resource_utils__

# include "defs.hpp"

# include <string>

namespace res
{
    /// Manages different pictures for different devices.
    std::string picture(const char *name);
    
    std::string animation_base_path(const char *name);
    std::string animation_frame(const char *path);
    
    /// Manages different resources for different devices.
    std::string sound_effect(const char *name);
    std::string background_sound(const char *name);
    
    std::string level_description(const char *name);
    
    std::string load_file_content(const std::string &file_name);
}

#endif /* defined(__areks__resource_utils__) */
