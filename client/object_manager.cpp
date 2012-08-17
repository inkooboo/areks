#include "object_manager.hpp"

#include <algorithm>

void ObjectManager::start()
{
}

void ObjectManager::stop()
{
    auto it = _objects.begin();
    auto end = _objects.end();

    for( ; it != end; ++it )
    {
        (*it)->destroy();
    }
}

ObjectManager::ObjectManager()
{
}

void ObjectManager::registerObject( BaseObject* obj_ptr )
{
    assert( std::find( _objects.begin(), _objects.end(), obj_ptr ) == _objects.end() );
    _objects.push_back( obj_ptr );
}

void ObjectManager::removeObject( BaseObject* obj_ptr )
{
    auto to_delete = std::find( _objects.begin(), _objects.end(), obj_ptr );
    assert( to_delete != _objects.end() );
    
    _objects.erase( to_delete );
}

void ObjectManager::registerDynamicObject( DynamicObject* obj_ptr )
{
    assert( std::find( _dyn_objects.begin(), _dyn_objects.end(), obj_ptr ) == _dyn_objects.end() );
    _dyn_objects.push_back( obj_ptr );
}

void ObjectManager::removeDynamicObject( DynamicObject* obj_ptr )
{
    auto to_delete = std::find( _dyn_objects.begin(), _dyn_objects.end(), obj_ptr );
    assert( to_delete != _dyn_objects.end() );
    
    _dyn_objects.erase( to_delete );
}

std::vector< BaseObject* >& ObjectManager::getObjects()
{
    return _objects;
}

std::vector< DynamicObject* >& ObjectManager::getDynamicObjects()
{
    return _dyn_objects;
}