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

# include <memory>

namespace effects 
{

    struct FlyingText : public EffectBase
    {
        static std::weak_ptr<FlyingText> create(const pr::Vec2 &position, cc::CCNode *parent, const char *text, size_t size, const cc::ccColor3B &color, float duration);
        
        virtual void update(float dt) override;
        virtual cc::CCNode * node() override;

    private:
        cc::CCLabelTTF *m_label;
        pr::Vec2 m_position;
    };
}

#endif /* defined(__areks__flying_text_effect__) */
