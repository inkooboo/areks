//
//  effect_base.hpp
//  areks
//
// Created by inkooboo on 9/4/12.
//
//

#ifndef __areks__base_effect__
#define __areks__base_effect__

# include "defs.hpp"

# include "noncopyable.hpp"

namespace effects 
{

    struct EffectBase : private noncopyable_t
    {
        virtual ~EffectBase() = 0;

        virtual void update(float dt) = 0;
        virtual cc::CCNode * node() = 0;
    };
}

#endif /* defined(__areks__base_effect__) */
