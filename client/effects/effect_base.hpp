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
        void schedule_deletion(cc::CCNode *effect_node);
    };
}

#endif /* defined(__areks__base_effect__) */
