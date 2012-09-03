#ifndef _AREKS_LOOP_HPP_
#define _AREKS_LOOP_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <functional>
# include <memory>
# include <list>

typedef std::function<void()> LazyFunction;
inline void lazyDoNothing() {};

class Loop : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    struct Scheduled : public cc::CCObject
    {
        Scheduled(LazyFunction handler, cc::CCScheduler *sched) : handler(handler), sched(sched), die_bitch(false) {}
        
        void func(float)
        {
            using namespace cocos2d;
            sched->unscheduleSelector( schedule_selector(Scheduled::func), this);
            handler();
            die_bitch = true;
        }

        LazyFunction handler;
        cc::CCScheduler *sched;
        bool die_bitch;
    };
    
public:
    Loop();
    
    void reload();

    void executeOnce(LazyFunction func);
    void schedule(LazyFunction func, float delay);

private:

    struct TimeLoop_t : public cc::CCObject
    {
        TimeLoop_t() : remainder(0.f) {}

        void update( float t );
        void executeOnce(LazyFunction func);

        float remainder;
        std::vector<LazyFunction> exec_once;        
        std::list<std::unique_ptr<Scheduled>> scheduled_list;
    };
    
    struct ViewLoop_t : public cc::CCObject
    {
        void tick( float t );   
    };
    
    TimeLoop_t _time_loop;
    ViewLoop_t _view_loop;
    
    cc::CCScheduler m_sheduler;
};

#endif