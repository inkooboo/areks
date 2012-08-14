#ifndef _AREKS_OBJECT_INTERFACES_HPP_
#define _AREKS_OBJECT_INTERFACES_HPP_

#include "defs.hpp"
#include "BaseObject.hpp"

class DynamicObject : BaseObject
{
public:
    DynamicObject();
    virtual ~DynamicObject() = 0;
    
    virtual Update( float t ) = 0;
};

class StaticObject : BaseObject
{
public:
    StaticObject();
    virtual ~StaticObject() = 0;
};

#endif