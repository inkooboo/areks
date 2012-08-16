#ifndef _AREKS_BASE_OBJECT_HPP_
#define _AREKS_BASE_OBJECT_HPP_

#include "defs.hpp"
#include "primitives.hpp"

class BaseObject
{
public:
    BaseObject();
    virtual ~BaseObject() = 0;
    
    virtual void draw() = 0;
    
    void draw_sprite_helper(cc::CCSprite *sprite, pr::Vec2 position);
};

#endif