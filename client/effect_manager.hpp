#ifndef _AREKS_EFFECT_MANAGER_HPP_
#define _AREKS_EFFECT_MANAGER_HPP_

# include "subsystem.hpp"
# include "effects/effect_base.hpp"

# include <list>
# include <memory>

class EffectManager : public subsystem_t
{
    virtual void start();
    virtual void stop();
    
public:
    EffectManager();
    
    void reload();

    
public: //do not call methods belo directly
    
    void update_effects(float dt);
    
    void add_effect(std::shared_ptr<effects::EffectBase> effect, float duration);
private:
    std::list<std::weak_ptr<effects::EffectBase>> m_effects_list;
};

#endif