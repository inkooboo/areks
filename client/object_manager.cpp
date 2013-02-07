#include "object_manager.hpp"

#include "master.hpp"
#include "loop.hpp"

#include "objects/ball.hpp"
#include "objects/enemy.hpp"
#include "objects/background.hpp"
#include "objects/platform.hpp"

#include <json/json.h>
#include <algorithm>

void delayed_object_creator(Json::Value description)
{
    master_t::subsystem<ObjectManager>().createObject(description);
    
    // schedule new creation if need
    bool repeat = description.get("repeat", false).asBool();
    float delay = description.get("appear_delay", 0.f).asFloat();
    if (repeat)
    {
        master_t::subsystem<Loop>().schedule(std::bind(delayed_object_creator, description), delay);
    }
}

void ObjectManager::start()
{
}

void ObjectManager::stop()
{
    _objects.clear();

    collect_garbage_objects();
}

ObjectManager::ObjectManager()
{
}

void ObjectManager::reload()
{
    stop();
    start();
}

void ObjectManager::addObject(std::shared_ptr<BaseObject> object)
{
    _objects.insert(object);
}

std::shared_ptr<BaseObject> ObjectManager::createObject(const Json::Value &description)
{
    std::shared_ptr<BaseObject> ret;
    
    if (description.isMember("appear_delay"))
    {
        float delay = description.get("appear_delay", 0.f).asFloat();
        master_t::subsystem<Loop>().schedule(std::bind(delayed_object_creator, description), delay);
        
        return ret;
    }

    const std::string class_name = description["class"].asString();
    // create object
    if (class_name == "ball")
    {
        ret.reset(new objects::Ball(description));
    }
    else if (class_name == "enemy")
    {
        ret.reset(new objects::Enemy(description));
    }
    else if (class_name == "background")
    {
        ret.reset(new objects::Background(description));
    }
    else if (class_name == "platform")
    {
        ret.reset(new objects::Platform(description));
    }
    // TODO ADD DEFAULT OBJECT
    
    //    else if ()
    //    {
    //    }
    
    addObject(ret);
    
    return ret;
}

void ObjectManager::destroyObject(std::shared_ptr<BaseObject> obj_ptr)
{
    auto to_del_it = _objects.find(obj_ptr);

    if (to_del_it == _objects.end())
    {
        return;
    }
    
    _to_delete_list.push_back(*to_del_it);
    
    _objects.erase(to_del_it);
}

void ObjectManager::update_dynamic_objects_state(float dt)
{
    for(auto obj : _objects)
    {
        obj->updateState(dt);
    }
}

void ObjectManager::update_objects(float dt)
{
    for(auto obj : _objects)
    {
        obj->draw();
    }    
}

void ObjectManager::collect_garbage_objects()
{
    _to_delete_list.clear();
}
