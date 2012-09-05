//
//  flying_text.cpp
//  areks
//
// Created by inkooboo on 9/4/12.
//
//

#include "flying_text.hpp"

#include "view.hpp"
#include "effect_manager.hpp"

namespace effects
{
    std::weak_ptr<FlyingText> FlyingText::create(const pr::Vec2 &position, cc::CCNode *parent, const char *text, size_t size, const cc::ccColor3B &color, float duration)
    {
        auto effect = std::make_shared<FlyingText>();
        
        effect->m_position = position;

        effect->m_label = cc::CCLabelTTF::create(text, "", size);
        effect->m_label->setColor(color);
        
        parent->addChild(effect->m_label);
        
        effect->update(0);
        
        master_t::subsystem<EffectManager>().add_effect(effect, duration);
        
        return effect;
    }

    void FlyingText::update(float dt)
    {
        m_position.x += dt;
        m_position.y += dt;
        
        master_t::subsystem<View>().drawSpriteHelper(m_label, m_position, 0);
    }

    cc::CCNode * FlyingText::node()
    {
        return m_label;
    }

}
