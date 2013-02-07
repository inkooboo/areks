#ifndef _AREKS_BASE_OBJECT_HPP_
#define _AREKS_BASE_OBJECT_HPP_

#include "defs.hpp"
#include "primitives.hpp"

#include <json/value.h>

class b2Body;
class b2Joint;

class BaseObject
{
public:
    virtual ~BaseObject() = 0;

    BaseObject(const Json::Value &description);
    
    virtual void draw() = 0;

    /**
     * physics group @{
     */
    virtual b2Body* getBody() = 0;
    virtual void collide( BaseObject* other, b2Contact *contact )
    {
    }
    virtual void deleteJoint( b2Joint* joint )
    {
    }
    void releaseJoints(b2Body* body);
    /**
     * }@
     */
    
    const  Json::Value & getDescription() const
    {
        return m_description;
    }
    
    /**
     * dynamic object group @{
     */
    virtual void updateState( float t )
    {
    }
    virtual pr::Vec2 getPosition() const
    {
        return pr::Vec2();
    }
    /**
     * }@
     */

protected:
    Json::Value m_description;
};


#endif