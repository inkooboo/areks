#include "Physics.hpp"

void Physics::start() {}
void Physics::strop() {}
    
Physics::Physics() 
{
    b2Vec2 gravity(0.0f, -10.0f);
    _b2World_ptr.reset( new b2World(gravity) );
}