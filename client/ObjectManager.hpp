#ifndef _AREKS_OBJECT_MANAGER_HPP_
#define _AREKS_OBJECT_MANAGER_HPP_

#include "subsystem.hpp"
#include "objects/BaseObject.hpp"

# include <vector>

class DynamicObject;

class ObjectManager : public subsystem_t
{
    virtual void start();
    virtual void stop();
    
public:
    ObjectManager();
    
    void registerObject( BaseObject* obj_ptr );
    void removeObject( BaseObject* obj_otr );
    
    void registerDynamicObject( DynamicObject* obj_ptr );
    void removeDynamicObject( DynamicObject* obj_ptr );

    std::vector< BaseObject* >& getObjects();
    std::vector< DynamicObject* >& getDynamicObjects();

    
private:
    std::vector< BaseObject* > _objects;
    std::vector< DynamicObject* > _dyn_objects;    
    
    
};

#endif