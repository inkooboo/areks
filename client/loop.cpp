#include "loop.hpp"

#include "master.hpp"

#include "object_manager.hpp"
#include "objects/object_interfaces.hpp"

#include "physics.hpp"
#include "view.hpp"

static const float DEFAULT_WORLD_TICK_TIME = 1.f/60.f;
static const float DEFAULT_VIEW_TICK_TIME = 1.f/40.f;

void Loop::start()
{
    resumeGame();
    resumeTime();
}

void Loop::stop() 
{ 
    pauseGame();
    pauseTime();
}

Loop::Loop()
{
    using namespace cocos2d;

    cc::CCDirector::sharedDirector()->setScheduler(this);

    cc::CCScheduler::scheduleUpdateForTarget( &_time_loop, 0, true);
    cc::CCScheduler::scheduleSelector( schedule_selector(ViewLoop_t::tick), &_view_loop, DEFAULT_VIEW_TICK_TIME, true);
}

void Loop::resumeTime()
{
    cc::CCScheduler::resumeTarget(&_time_loop);
}

void Loop::pauseTime()
{
    cc::CCScheduler::pauseTarget(&_time_loop);
}

void Loop::resumeGame()
{
    cc::CCScheduler::resumeTarget(&_view_loop);
}

void Loop::pauseGame()
{
    cc::CCScheduler::pauseTarget(&_view_loop);
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

    //delegate management to ObjectManager
    master_t::subsystem<ObjectManager>().update();
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
