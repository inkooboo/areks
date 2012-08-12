#ifndef _AREKS_LOOP_HPP_
#define _AREKS_LOOP_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

class Loop : public cc::CCScheduler, public subsystem_t
{
public:
    virtual void start();
    virtual void stop();

    Loop();

    void Resume();

    void Pause();

    void tick(float t);
};

#endif