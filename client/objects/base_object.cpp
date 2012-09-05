#include "base_object.hpp"

#include "master.hpp"

#include "object_manager.hpp"
#include "view.hpp"

BaseObject::BaseObject()
{
    master_t::subsystem<ObjectManager>().registerObject(this);
}

BaseObject::~BaseObject()
{
    master_t::subsystem<ObjectManager>().removeObject(this);
}

void BaseObject::destroy()
{
    master_t::subsystem<ObjectManager>().destroyObject( this );
}

void BaseObject::releaseJoints( b2Body* body )
{
    b2JointEdge* j_e = body->GetJointList();
    for( ; j_e; j_e = j_e->next )
    {
        b2Joint* joint = j_e->joint;
        b2Body* cur_body;
        if( body == joint->GetBodyA() )
        {
            cur_body = joint->GetBodyB();
        }
        else
        {
            cur_body = joint->GetBodyA();
        }

        BaseObject* obj = static_cast<BaseObject*>( cur_body->GetUserData() );
        obj->deleteJoint( joint );
    }
}
