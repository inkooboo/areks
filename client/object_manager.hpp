#ifndef _AREKS_OBJECT_MANAGER_HPP_
#define _AREKS_OBJECT_MANAGER_HPP_

#include "subsystem.hpp"
#include "objects/base_object.hpp"

# include <json/json.h>
# include <set>
# include <list>
# include <memory>

class ObjectManager : public subsystem_t
{
    virtual void start();
    virtual void stop();
    
public:
    ObjectManager();
    
    void reload();
    
    std::shared_ptr<BaseObject> createObject(const Json::Value &description);
    void destroyObject(std::shared_ptr<BaseObject> obj_ptr);
    void addObject(std::shared_ptr<BaseObject> object);

    void update_dynamic_objects_state(float dt);
    void update_objects(float dt);
    void collect_garbage_objects();
                               
private:
    std::set<std::shared_ptr<BaseObject>> _objects;

    std::list<std::shared_ptr<BaseObject>> _to_delete_list;
};

#endif