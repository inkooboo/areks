#ifndef _AREKS_PHYSICS_HPP_
#define _AREKS_PHYSICS_HPP_

# include "subsystem.hpp"
# include "primitives.hpp"

# include <Box2D/Box2D.h>

//managed subsystem Physics
class Physics : public subsystem_t 
{
    virtual void start() override;
    virtual void stop() override;

public:    
    Physics();

    b2World* worldEngine();
    
    pr::Vec2 worldSize() const;
	
	//don't call this method manually!
    void step( float dt );
private:
    std::unique_ptr<b2World> _b2World_ptr;
    pr::Vec2 m_world_size;
};

#endif