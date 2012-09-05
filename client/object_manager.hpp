#ifndef _AREKS_OBJECT_MANAGER_HPP_
#define _AREKS_OBJECT_MANAGER_HPP_

#include "subsystem.hpp"
#include "objects/base_object.hpp"

# include <vector>

class DynamicObject;

class ObjectManager : public subsystem_t
{
    virtual void start();
    virtual void stop();
    
public:
    ObjectManager();
    
    void reload();
    
    //don't uses this methods manually!
    void registerObject( BaseObject* obj_ptr );
    void removeObject( BaseObject* obj_otr );

    //don't uses this methods manually!
    void registerDynamicObject( DynamicObject* obj_ptr );
    void removeDynamicObject( DynamicObject* obj_ptr );

    void destroyObject( BaseObject* obj_ptr );

    void update_dynamic_objects_state(float dt);
    void update_objects(float dt);
    
    void collect_garbage_objects();
    
private:
    std::vector< BaseObject* > _objects;
    std::vector< DynamicObject* > _dyn_objects;

    std::vector<BaseObject*> _to_delete_list;
};

#endif