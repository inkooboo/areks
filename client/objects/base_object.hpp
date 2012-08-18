#ifndef _AREKS_BASE_OBJECT_HPP_
#define _AREKS_BASE_OBJECT_HPP_

#include "defs.hpp"
#include "primitives.hpp"

class b2Body;

class BaseObject
{
public:
    BaseObject();
    virtual ~BaseObject() = 0;
    
    virtual void draw() = 0;

    virtual b2Body* getBody() = 0;
	
	//possible remake this for lazy destruction
    void destroy();
    
    void draw_sprite_helper(cc::CCSprite *sprite, pr::Vec2 position, float angle);
};

namespace objects 
{
}

#endif