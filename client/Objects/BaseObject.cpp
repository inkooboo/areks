#include "BaseObject.hpp"

#include "master.hpp"

#include "ObjectManager.hpp"

BaseObject::BaseObject()
{
    master_t::subsystem<ObjectManager>().registerObject(this);
}

BaseObject::~BaseObject()
{
    master_t::subsystem<ObjectManager>().removeObject(this);
}