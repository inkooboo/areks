#include "physics.hpp"

#include "level_loader.hpp"

#include "objects/base_object.hpp"

static const float TOUCH_ACCURACY = 0.001f;

void ContactListener::BeginContact(b2Contact *contact)
{
    BaseObject* obj_a = static_cast<BaseObject*>( contact->GetFixtureA()->GetBody()->GetUserData() );
    BaseObject* obj_b = static_cast<BaseObject*>( contact->GetFixtureB()->GetBody()->GetUserData() );

    obj_a->collide( obj_b, contact );
    obj_b->collide( obj_a, contact );
}

void Physics::start()
{
    b2Vec2 gravity(0.0f, -10.0f);
    _b2World_ptr.reset( new b2World(gravity) );
    _b2World_ptr->SetAllowSleeping( true );
    
    // Set contact listener
    _b2World_ptr->SetContactListener(&_contact_listener);
}

void Physics::stop()
{
}
    
Physics::Physics() 
{
}

void Physics::reload(pr::Vec2 world_size)
{
    stop();
    start();
    m_world_size = world_size;
}

b2World* Physics::worldEngine()
{
    assert( ! _b2World_ptr->IsLocked() && "Physics in handle process. Can not access non const world object!");
    return _b2World_ptr.get();
}

b2World* const Physics::worldEngine() const
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

    for( auto it = _joint_defs.begin(), end = _joint_defs.end(); it != end; ++it )
    {
        _b2World_ptr->CreateJoint( it->get() );
    }
    _joint_defs.clear();
    
    _b2World_ptr->Step( dt, velocityIterations, positionIterations );

	//execute lazy calculations
    for( auto it = _to_exec_funcs.begin(), end = _to_exec_funcs.end(); it != end; ++it )
    {
        (*it)();
    }
    _to_exec_funcs.clear();
}

class OneObjectQueryCallback : public b2QueryCallback
{
public:
    OneObjectQueryCallback()
        : result_obj(0)
    { }

    bool ReportFixture(b2Fixture* fixture)
    {
        result_obj = static_cast<BaseObject*>( fixture->GetBody()->GetUserData() );

        // Return false to break the query.
        return false;
    }

    BaseObject* result_obj;
};

BaseObject* Physics::getObject( pr::Vec2 const& point )
{    
    b2AABB aabb;
    aabb.lowerBound = b2Vec2( point.x - TOUCH_ACCURACY, point.y - TOUCH_ACCURACY );
    aabb.upperBound = b2Vec2( point.x + TOUCH_ACCURACY, point.y + TOUCH_ACCURACY );
    
    OneObjectQueryCallback callback;
    _b2World_ptr->QueryAABB( &callback, aabb );

    return callback.result_obj;
}

class CheckObjectQueryCallback : public b2QueryCallback
{
public:
    CheckObjectQueryCallback(BaseObject* obj)
        : result(false)
		, obj(obj)
    { }

    bool ReportFixture(b2Fixture* fixture)
    {
        result = (obj == static_cast<BaseObject*>(fixture->GetBody()->GetUserData()) );

        // Return false to break the query or true to continue.
        return (!result);
    }

    bool result;
	BaseObject* obj;
};

bool Physics::checkObject(pr::Vec2 const& point, BaseObject* obj)
{
    b2AABB aabb;
    aabb.lowerBound = b2Vec2( point.x - TOUCH_ACCURACY, point.y - TOUCH_ACCURACY );
    aabb.upperBound = b2Vec2( point.x + TOUCH_ACCURACY, point.y + TOUCH_ACCURACY );
    
    CheckObjectQueryCallback callback(obj);
    _b2World_ptr->QueryAABB( &callback, aabb );

    return callback.result;	
}

BodyOwner Physics::CreateBody( defs::OneShapeBaseDef& def )
{
    assert( def.check() && "Error in init body!" );
    BodyOwner ret( _b2World_ptr->CreateBody( def.getBodyDef() ) );
    ret->CreateFixture( def.getFixtureDef() );
    return ret;
}

void Physics::execute_after_step( LazyFunction func )
{
	_to_exec_funcs.push_back( func );
}

