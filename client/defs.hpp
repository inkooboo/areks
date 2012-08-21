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

#if defined(__GNUC__) && !defined(__clang__) // gcc will support override since 4.7 version
# define override 
#endif

//for using std::max
#ifdef _WINDOWS
    #undef max
#endif

#endif