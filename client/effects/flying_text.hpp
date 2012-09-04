//
//  flying_text.hpp
//  areks
//
// Created by inkooboo on 9/4/12.
//
//

#ifndef __areks__flying_text_effect__
#define __areks__flying_text_effect__

# include "defs.hpp"
# include "primitives.hpp"

# include "effect_base.hpp"

# include <label_nodes/CCLabelTTF.h>

namespace effects 
{

    struct FlyingText : public cc::CCLabelTTF, public EffectBase
    {
        static FlyingText * create(const pr::Vec2 &position, cc::CCNode *parent, const char *text, size_t size, const cc::ccColor3B &var);
    };
}

#endif /* defined(__areks__flying_text_effect__) */
