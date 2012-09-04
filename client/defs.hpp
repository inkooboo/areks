#ifndef _AREKS_DEFS_HPP_
#define _AREKS_DEFS_HPP_


/// TODO: Use this file as precompiled header


# include <cocos2d.h>
# include <Box2D/Box2D.h>
# include "CCEGLView.h"
# include "CCFileUtils.h"
# include "SimpleAudioEngine.h"

# include <memory>

namespace cc = cocos2d;
namespace cd = CocosDenshion;

// development defines
#define NO_MENU
#define NO_SOUND




#if defined(__GNUC__) && !defined(__clang__) // gcc will support "override" since 4.7 version
# define override 
#endif

//for using std::max, std::min
#ifdef _WINDOWS
    #undef max
	#undef min
#endif

namespace group
{
    enum
    {
        PLAYER = -1
    };
}

namespace filter
{
    enum
    {
		NONE = 0,

        PLATFORMS = 1,
		OBJECTS = 1 << 1,
		HEAD = 1 << 2,
		NECK = 1 << 3,

		ALL = 0xffff
    };
}

#endif