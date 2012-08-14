#ifndef _AREKS_LOOP_HPP_
#define _AREKS_LOOP_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

class Loop : public cc::CCScheduler, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    Loop();

    void resumeTime();
    void pauseTime();
    
    void resumeGame();
    void pauseGame();

private:

    class TimeLoop_t : public cc::CCObject
    {
    public:
        tick( float t );
        
    };
    
    class ViewLoop_t : public cc::CCObject
    {
    public:
        tick( float t );
        
    };
    
    TimeLoop_t _time_loop;
    ViewLoop_t _view_loop;    
    //void tick(float t);
};

#endif