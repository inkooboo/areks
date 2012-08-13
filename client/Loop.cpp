#include "Loop.hpp"

void Loop::start()
{ 
}

void Loop::stop() 
{ 
    this->Pause();
}

Loop::Loop()
{
    using namespace cocos2d;

    cc::CCDirector::sharedDirector()->setScheduler(this);

    cc::CCScheduler::scheduleSelector( schedule_selector(Loop::tick), this, 1.f, false);
}

void Loop::Resume()
{
    cc::CCScheduler::pauseTarget(this);
}

void Loop::Pause()
{
    cc::CCScheduler::resumeTarget(this);
}

void Loop::tick(float t)
{
}