#ifndef _AREKS_LOOP_HPP_
#define _AREKS_LOOP_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <functional>
# include <memory>
# include <list>

inline void lazyDoNothing() {};

class Loop : public subsystem_t, public cc::CCObject
{
    virtual void start() override;
    virtual void stop() override;

public:
    Loop();
    
    void reload();
    
    void schedule(LazyFunction func, float delay);
    
    virtual void update(float dt) override;

    void update_view(float dt);

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
    
private:
    std::list<std::unique_ptr<Scheduled>> m_scheduled_list;
    float m_reminder;
    cc::CCScheduler m_sheduler;
};

#endif