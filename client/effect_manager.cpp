#include "effect_manager.hpp"

#include "master.hpp"
#include "loop.hpp"

#include <functional>

void EffectManager::start()
{
}

void EffectManager::stop()
{
    m_effects_list.clear();
}

EffectManager::EffectManager()
{
}

void EffectManager::reload()
{
    stop();
    start();
}

void holding_effect_deleter(std::shared_ptr<effects::EffectBase> effect)
{
    effect->node()->removeFromParentAndCleanup(true);
}

void EffectManager::add_effect(std::shared_ptr<effects::EffectBase> effect, float duration)
{
    m_effects_list.push_back(std::weak_ptr<effects::EffectBase>(effect));
    
    master_t::subsystem<Loop>().schedule(std::bind(holding_effect_deleter, effect), duration);
}


void EffectManager::update_effects(float dt)
{
    for (auto it = m_effects_list.begin(); it != m_effects_list.end();)
    {
        auto shared = it->lock();
        if (shared)
        {
            shared->update(dt);
            ++it;
        }
        else
        {
            it = m_effects_list.erase(it);
        }
    }
}
