#ifndef _AREKS_DEFS_HPP_
#define _AREKS_DEFS_HPP_

# include <cocos2d.h>
# include <memory>

namespace cc = cocos2d;

#if defined(__GNUC__)
# define override 
#endif

//for using std::max
#ifdef _WINDOWS
    #undef max
#endif

#endif