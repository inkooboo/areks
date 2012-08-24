#ifndef _AREKS_OBJECT_PLATFORM_HPP_
#define _AREKS_OBJECT_PLATFORM_HPP_

#include "defs.hpp"
#include "object_interfaces.hpp"

#include "primitives.hpp"
#include "body_definitions.hpp"

namespace objects
{

    class Platform : public StaticObject
    {
    public:
        static Platform* create(const pr::Vec2* vertices, size_t count);
        
        virtual void draw() override;

        virtual b2Body* getBody() override;
        
    private:
        Platform(const pr::Vec2* vertices, size_t count);
        ~Platform();

        BodyOwner _body;
        cc::CCSprite* _sprite;
    };
    
}//end namespace objects

#endif