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

void BaseObject::addSprite(cc::CCSprite *sprite)
{
    master_t::subsystem<View>().gameLayer()->addChild( sprite );
}

void BaseObject::removeSprite(cc::CCSprite *sprite)
{
    sprite->removeFromParentAndCleanup(true);
}

void BaseObject::drawSpriteHelper(cc::CCSprite *sprite, pr::Vec2 position, float angle)
{
    const cc::CCPoint &prev_position = sprite->getPosition();
    cc::CCPoint cur_position = master_t::subsystem<View>().toScreenCoordinates(position);
    if (prev_position.x != cur_position.x || prev_position.y != cur_position.y)
    {
        sprite->setPosition(cur_position);
    }
    
    float prev_scale = sprite->getScale();
    float cur_scale = master_t::subsystem<View>().pixelScale();
    if (prev_scale != cur_scale)
    {
        sprite->setScale(cur_scale);
    }

    //rotation in Box2d - in radiance
    //rotation in cocos2d-x - in degrees
    float prev_angle = sprite->getRotation();
    float cur_angle = -angle * 180/b2_pi; //FIXME minus ??? are you sure?
    if (prev_angle != angle)
    {
        sprite->setRotation( cur_angle );
    }
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
