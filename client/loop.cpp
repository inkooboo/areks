#include "loop.hpp"

#include "master.hpp"

#include "object_manager.hpp"
#include "objects/object_interfaces.hpp"

void Loop::start()
{
    this->resumeGame();
}

void Loop::stop() 
{ 
    this->pauseGame();
}

Loop::Loop()
{
    using namespace cocos2d;

    cc::CCDirector::sharedDirector()->setScheduler(this);

    cc::CCScheduler::scheduleSelector( schedule_selector(TimeLoop_t::tick), &_time_loop, 1.f, true);
    cc::CCScheduler::scheduleUpdateForTarget( &_view_loop, 0, true);
}

void Loop::resumeTime()
{
    cc::CCScheduler::pauseTarget(&_time_loop);
}

void Loop::pauseTime()
{
    cc::CCScheduler::resumeTarget(&_time_loop);
}

void Loop::resumeGame()
{
    cc::CCScheduler::pauseTarget(&_view_loop);
}

void Loop::pauseGame()
{
    cc::CCScheduler::resumeTarget(&_view_loop);
}

void Loop::TimeLoop_t::tick(float t)
{
    auto objects = master_t::subsystem<ObjectManager>().getDynamicObjects();
    auto it = objects.begin();
    auto end = objects.end();
    
    for( ; it != end; ++it )
    {
        (*it)->updateState( t );
    }
}

void Loop::ViewLoop_t::update( float t )
{
    auto objects = master_t::subsystem<ObjectManager>().getObjects();
    auto it = objects.begin();
    auto end = objects.end();
    
    for( ; it != end; ++it )
    {
        (*it)->draw();
    }
}
