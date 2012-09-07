#ifndef _AREKS_PHYSICS_HPP_
#define _AREKS_PHYSICS_HPP_

# include "subsystem.hpp"
# include "primitives.hpp"

# include "defs.hpp"

# include "body_definitions.hpp"

class ContactListener : public b2ContactListener
{
public:
    ContactListener()
        : b2ContactListener()
    {}

    void BeginContact(b2Contact *contact);
};

class BaseObject;

//managed subsystem Physics
class Physics : public subsystem_t 
{
    virtual void start() override;
    virtual void stop() override;

public:    
    Physics();
    
    void reload(pr::Vec2 world_size);

    b2World* worldEngine();
    b2World* const worldEngine() const;
    
    pr::Vec2 worldSize() const;
	
	//don't call this method manually!
    void step( float dt );

    BaseObject* getObject(pr::Vec2 const& point);
	bool checkObject(pr::Vec2 const& point, BaseObject* obj);

    BodyOwner CreateBody( defs::OneShapeBaseDef& def );

	void execute_after_step( LazyFunction func );

private:
    std::unique_ptr<b2World> _b2World_ptr;
    pr::Vec2 m_world_size;

    ContactListener _contact_listener;

    std::vector<shared_ptr<b2JointDef> > _joint_defs;

	std::vector<LazyFunction> _to_exec_funcs;
};

#endif