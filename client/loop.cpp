#include "loop.hpp"

#include "master.hpp"

#include "object_manager.hpp"
#include "objects/object_interfaces.hpp"

#include "physics.hpp"
#include "view.hpp"

static const float DEFAULT_WORLD_TICK_TIME = 1.f/60.f;
static const float DEFAULT_VIEW_TICK_TIME = 1.f/40.f;

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
    m_sheduler.unscheduleAllSelectors();
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
    Scheduled *sch = new Scheduled(func, &m_sheduler);
    m_sheduler.scheduleSelector( schedule_selector(Scheduled::func), sch, 0, false, 0, delay);
}

void Loop::TimeLoop_t::update(float t)
{
    float ft = t + _remainder;

    float diff = DEFAULT_WORLD_TICK_TIME;
    while (ft > 0)
    {
        if (ft - DEFAULT_WORLD_TICK_TIME < 0)
        {
            _remainder = ft;
        }
        else
        {
            master_t::subsystem<Physics>().step( diff );
        }
        ft -= DEFAULT_WORLD_TICK_TIME;
    }

    t -= _remainder; // calculate real time
    
    master_t::subsystem<View>().onRescaleTick(t); // manage dynamic scale
    
    
    auto objects = master_t::subsystem<ObjectManager>().getDynamicObjects();
    auto it = objects.begin();
    auto end = objects.end();
    
    for( ; it != end; ++it )
    {
        (*it)->updateState( t );
    }

    //execute lazy calculations
    for( auto it = _exec_once.begin(), end = _exec_once.end(); it != end; ++it )
    {
        (*it)();
    }
    _exec_once.clear();

    //delegate management to ObjectManager
    master_t::subsystem<ObjectManager>().update();
}

void Loop::TimeLoop_t::executeOnce(std::function<void()> func)
{
    _exec_once.push_back( func );
}

void Loop::ViewLoop_t::tick( float t )
{
    auto objects = master_t::subsystem<ObjectManager>().getObjects();
    auto it = objects.begin();
    auto end = objects.end();
    
    for( ; it != end; ++it )
    {
        (*it)->draw();
    }
}
