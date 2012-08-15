#include "object_interfaces.hpp"

#include "master.hpp"

#include "object_manager.hpp"


DynamicObject::DynamicObject()
    : BaseObject()
{
    master_t::subsystem<ObjectManager>().registerDynamicObject( this );
}

DynamicObject::~DynamicObject()
{
    master_t::subsystem<ObjectManager>().removeDynamicObject( this );
}

StaticObject::StaticObject()
    : BaseObject()
{
}

StaticObject::~StaticObject()
{
}
