#ifndef _AREKS_BASE_OBJECT_HPP_
#define _AREKS_BASE_OBJECT_HPP_

#include "defs.hpp"

class BaseObject
{
public:
    BaseObject();
    virtual ~BaseObject() = 0;
    
    virtual void draw() = 0;
    
};

#endif