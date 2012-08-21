#include "physics.hpp"

#include "level_manager.hpp"

#include "objects/base_object.hpp"

void ContactListener::BeginContact(b2Contact *contact)
{
    BaseObject* obj_a = static_cast<BaseObject*>( contact->GetFixtureA()->GetBody()->GetUserData() );
    BaseObject* obj_b = static_cast<BaseObject*>( contact->GetFixtureB()->GetBody()->GetUserData() );

    obj_a->collide( obj_b );
    obj_b->collide( obj_a );
}

void Physics::start()
{
    m_world_size = master_t::subsystem<LevelManager>().worldSize();
}

void Physics::stop() {}
    
Physics::Physics() 
{
    b2Vec2 gravity(0.0f, -10.0f);
    bool doSleep = true;
    _b2World_ptr.reset( new b2World(gravity) );
    _b2World_ptr->SetAllowSleeping( doSleep );

    // Set contact listener
    _b2World_ptr->SetContactListener(&_contact_listener);
}

b2World* Physics::worldEngine()
{
    return _b2World_ptr.get();
}

pr::Vec2 Physics::worldSize() const
{
    return m_world_size;
}

void Physics::step( float dt )
{
    static int velocityIterations = 8;
    static int positionIterations = 3;
    
    _b2World_ptr->Step( dt, velocityIterations, positionIterations );
}
