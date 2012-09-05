#include "loop.hpp"

#include "master.hpp"

#include "object_manager.hpp"
#include "objects/object_interfaces.hpp"

#include "physics.hpp"
#include "view.hpp"
#include "effect_manager.hpp"

static const float DEFAULT_WORLD_TICK_TIME = 1.f/60.f;
static const float DEFAULT_VIEW_TICK_TIME = 1.f/33.f;

Loop::Loop()
{
    using namespace cocos2d;
    cc::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget( &m_sheduler, 0, false);
}

void Loop::start()
{
    using namespace cocos2d;
    m_sheduler.scheduleUpdateForTarget( &_time_loop, 0, false);
    m_sheduler.scheduleSelector( schedule_selector(ViewLoop_t::tick), &_view_loop, DEFAULT_VIEW_TICK_TIME, false);
}

void Loop::stop() 
{ 
    m_sheduler.unscheduleAllSelectors(); //FIXME our shedules will never destroy (they mark themselfs to destory on func() )
}

void Loop::reload()
{
    stop();
    start();
}

void Loop::executeOnce(LazyFunction func)
{
    _time_loop.executeOnce( func );
}

void Loop::schedule(LazyFunction func, float delay)
{
    using namespace cocos2d;
    _time_loop.scheduled_list.push_back(std::unique_ptr<Scheduled>(new Scheduled(func, &m_sheduler)));
    Scheduled *sch = _time_loop.scheduled_list.back().get();
    m_sheduler.scheduleSelector( schedule_selector(Scheduled::func), sch, 0, false, 0, delay);
}

void Loop::TimeLoop_t::update(float t)
{
	//FOR TEST
	t *= 1.4f;
	//

    float ft = t + remainder;

    float diff = DEFAULT_WORLD_TICK_TIME;
    while (ft > 0)
    {
        if (ft - DEFAULT_WORLD_TICK_TIME < 0)
        {
            remainder = ft;
        }
        else
        {
            master_t::subsystem<Physics>().step( diff );
        }
        ft -= DEFAULT_WORLD_TICK_TIME;
    }

    t -= remainder; // calculate real time
    
    master_t::subsystem<View>().onRescaleTick(t); // manage dynamic scale
    
    master_t::subsystem<ObjectManager>().update_dynamic_objects_state(t);

    //execute lazy calculations
    for( auto it = exec_once.begin(), end = exec_once.end(); it != end; ++it )
    {
        (*it)();
    }
    exec_once.clear();

    //delegate management to ObjectManager
    master_t::subsystem<ObjectManager>().collect_garbage_objects();

    // remove scheduled items
    for (auto it = scheduled_list.begin(), end = scheduled_list.end(); it != end;)
    {
        if ((*it)->die_bitch)
        {
            it = scheduled_list.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Loop::TimeLoop_t::executeOnce(std::function<void()> func)
{
    exec_once.push_back( func );
}

void Loop::ViewLoop_t::tick( float t )
{
    master_t::subsystem<ObjectManager>().update_objects(t);
    
    master_t::subsystem<EffectManager>().update_effects(t);
}
