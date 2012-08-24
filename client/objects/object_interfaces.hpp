#ifndef _AREKS_OBJECT_INTERFACES_HPP_
#define _AREKS_OBJECT_INTERFACES_HPP_

#include "defs.hpp"
#include "base_object.hpp"
#include "primitives.hpp"

class DynamicObject : public BaseObject
{
public:
    DynamicObject();
    virtual ~DynamicObject() = 0;
    
    virtual void updateState( float t ) = 0;

    virtual pr::Vec2 getPosition() const = 0;
};

class StaticObject : public BaseObject
{
public:
    StaticObject();
    virtual ~StaticObject() = 0;
};

#endif