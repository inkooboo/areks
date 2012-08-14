#ifndef _AREKS_PHYSICS_HPP_
#define _AREKS_PHYSICS_HPP_

# include "subsystem.hpp"

# include <Box2D/Box2D.h>

//managed subsystem Physics
class Physics : public subsystem_t 
{
    virtual void start() override;
    virtual void stop() override;

public:    
    Physics();

    b2World* worldEngine();
    
    //temp for scene navigation logic
    b2Vec2 worldSize() const
    {
        return b2Vec2(48.f, 32.f); // we should create world and background with corresponding propotions
    }
    
private:
    std::unique_ptr<b2World> _b2World_ptr;
};

#endif