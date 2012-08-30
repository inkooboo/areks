#ifndef _AREKS_LOOP_HPP_
#define _AREKS_LOOP_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <functional>

class Loop : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    typedef std::function<void()> LazyFunction;

public:
    Loop();

    void resumeTime();
    void pauseTime();
    
    void resumeGame();
    void pauseGame();

    void executeOnce(std::function<void()>& func);

private:

    class TimeLoop_t : public cc::CCObject
    {
    public:
        TimeLoop_t()
            : _remainder(0)
        { }

        void update( float t );

        void executeOnce(std::function<void()>& func);

    private:
        float _remainder;

        std::vector<std::function<void()> > _exec_once;        
    };
    
    class ViewLoop_t : public cc::CCObject
    {
    public:
        void tick( float t );   
    };
    
    TimeLoop_t _time_loop;
    ViewLoop_t _view_loop;    
    //void tick(float t);
};

#endif