#ifndef _AREKS_PHYSICS_HPP_
#define _AREKS_PHYSICS_HPP_

# include "subsystem.hpp"

# include <Box2D/Box2D.h>

//managed subsystem Physics
class Physics : public subsystem_t 
{
public:
    //subsytems methods
    virtual void start();
    virtual void strop();
    
    Physics();

private:
    std::unique_ptr<b2World> _b2World_ptr;

};

#endif