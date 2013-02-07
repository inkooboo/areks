#include "loop.hpp"

#include "master.hpp"

#include "object_manager.hpp"

#include "physics.hpp"
#include "view.hpp"
#include "effect_manager.hpp"

static const float DEFAULT_WORLD_TICK_TIME = 1.f/60.f;
static const float DEFAULT_VIEW_TICK_TIME = 1.f/33.f;
static const float BOOST_GAME_SPEED = 1.4f;

Loop::Loop()
    : m_reminder(0)
{
    using namespace cocos2d;
    cc::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget( &m_sheduler, 0, false);
}

void Loop::start()
{
    using namespace cocos2d;
    m_sheduler.scheduleUpdateForTarget(this, 0, false);
    m_sheduler.scheduleSelector(schedule_selector(Loop::update_view), this, DEFAULT_VIEW_TICK_TIME, false);
}

void Loop::stop() 
{ 
    m_sheduler.unscheduleAllSelectors();
    m_scheduled_list.clear();
    m_reminder = 0;
}

void Loop::reload()
{
    stop();
    start();
}

void Loop::schedule(LazyFunction func, float delay)
{
    using namespace cocos2d;
    m_scheduled_list.push_back(std::unique_ptr<Scheduled>(new Scheduled(func, &m_sheduler)));
    Scheduled *sch = m_scheduled_list.back().get();
    m_sheduler.scheduleSelector( schedule_selector(Scheduled::func), sch, 0, false, 0, delay);
}

void Loop::update(float delta)
{
	delta *= BOOST_GAME_SPEED; // speed up game time


    float corrected_delta = delta + m_reminder; // add reminder from previous tick

    while (corrected_delta > DEFAULT_WORLD_TICK_TIME) // step physics
    {
        master_t::subsystem<Physics>().step(DEFAULT_WORLD_TICK_TIME);
        corrected_delta -= DEFAULT_WORLD_TICK_TIME;
    }
    
    m_reminder = corrected_delta; // new reminder

    delta -= m_reminder; // set delta to time passed in physics
    

    master_t::subsystem<View>().manageCameraPositionAndScale(delta); // manage dynamic scale
    

    master_t::subsystem<ObjectManager>().update_dynamic_objects_state(delta);
    master_t::subsystem<ObjectManager>().collect_garbage_objects();


    // remove scheduled items
    for (auto it = m_scheduled_list.begin(), end = m_scheduled_list.end(); it != end;)
    {
        if ((*it)->die_bitch)
        {
            it = m_scheduled_list.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Loop::update_view(float dt)
{
    master_t::subsystem<ObjectManager>().update_objects(dt);
    
    master_t::subsystem<EffectManager>().update_effects(dt);
}
