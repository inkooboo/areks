//
//  arrow.cpp
//  areks
//
//  Created by inkooboo on 9/5/12.
//
//

#include "arrow.hpp"

#include "view.hpp"
#include "effect_manager.hpp"
#include "resource_utils.hpp"

namespace effects
{
    std::weak_ptr<Arrow> Arrow::create(const pr::Vec2 &position, cc::CCNode *parent, float direction, float duration)
    {
        auto effect = std::make_shared<Arrow>();
        
        effect->m_direction = direction;
        effect->m_position = position;
        
        effect->m_sprite = cc::CCSprite::create(res::picture("arrow").c_str());
        
        parent->addChild(effect->m_sprite);
        
        effect->update(0);
        
        master_t::subsystem<EffectManager>().add_effect(effect, duration);
        
        return effect;
    }
    
    void Arrow::update_position(const pr::Vec2 &position)
    {
        m_position = position;
    }
    
    void Arrow::update_direction(float direction)
    {
        m_direction = direction;
    }

    void Arrow::update(float dt)
    {
        master_t::subsystem<View>().drawSpriteHelper(m_sprite, m_position, m_direction);
    }
    
    cc::CCNode * Arrow::node()
    {
        return m_sprite;
    }
    
}
