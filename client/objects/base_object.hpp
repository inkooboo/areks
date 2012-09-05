#ifndef _AREKS_BASE_OBJECT_HPP_
#define _AREKS_BASE_OBJECT_HPP_

#include "defs.hpp"
#include "primitives.hpp"

class b2Body;
class b2Joint;

class BaseObject
{
public:
    BaseObject();
    virtual ~BaseObject() = 0;
    
    virtual void draw() = 0;

    virtual b2Body* getBody() = 0;

    virtual void collide( BaseObject* other, b2Contact *contact ) { }

    virtual void deleteJoint( b2Joint* joint ) { }
	
    void destroy();
    
    void releaseJoints(b2Body* body);
};

namespace objects 
{
}

#endif