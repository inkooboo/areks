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
//    delete this;
}

void BaseObject::draw_sprite_helper(cc::CCSprite *sprite, pr::Vec2 position)
{
    const cc::CCPoint &prev_position = sprite->getPosition();
    cc::CCPoint cur_position = master_t::subsystem<View>().toScreenCoordinates(position);
    if (prev_position.x != cur_position.x || prev_position.y != cur_position.y)
    {
        sprite->setPosition(cur_position);
    }
    
    float prev_scale = sprite->getScale();
    float cur_scale = master_t::subsystem<View>().pixel_scale();
    if (prev_scale != cur_scale)
    {
        sprite->setScale(cur_scale);
    }
}
