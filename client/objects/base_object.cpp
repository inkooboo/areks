#include "base_object.hpp"

#include "master.hpp"

#include "object_manager.hpp"

BaseObject::BaseObject()
{
    master_t::subsystem<ObjectManager>().registerObject(this);
}

BaseObject::~BaseObject()
{
    master_t::subsystem<ObjectManager>().removeObject(this);
}