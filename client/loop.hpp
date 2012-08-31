#ifndef _AREKS_LOOP_HPP_
#define _AREKS_LOOP_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <functional>

typedef std::function<void()> LazyFunction;
inline void lazyDoNothing() {};

class Loop : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    struct Scheduled : public cc::CCObject
    {
        Scheduled(LazyFunction func, cc::CCScheduler *sched) : m_func(func), m_sched(sched) {}
        
        void func(float)
        {
            using namespace cocos2d;
            m_sched->unscheduleSelector( schedule_selector(Scheduled::func), this);
            m_func();
            delete this;
        }
        LazyFunction m_func;
        cc::CCScheduler *m_sched;
    };
    
public:
    Loop();
    
    void reload();

    void executeOnce(LazyFunction func);
    void schedule(LazyFunction func, float delay);

private:

    class TimeLoop_t : public cc::CCObject
    {
    public:
        TimeLoop_t()
            : _remainder(0)
        { }

        void update( float t );

        void executeOnce(LazyFunction func);

    private:
        float _remainder;

        std::vector<LazyFunction> _exec_once;        
    };
    
    class ViewLoop_t : public cc::CCObject
    {
    public:
        void tick( float t );   
    };
    
    TimeLoop_t _time_loop;
    ViewLoop_t _view_loop;
    
    cc::CCScheduler m_sheduler;
    //void tick(float t);
};

#endif