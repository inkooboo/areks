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
        static Platform* create(pr::Vec2 const& coordinates, pr::Vec2 const& size);
        
        virtual void draw() override;

        virtual b2Body* getBody() override;
        
    private:
        Platform(pr::Vec2 const& coordinates, pr::Vec2 const& size);
        ~Platform();

        BodyOwner _body;
        cc::CCSprite* _sprite;
        pr::Vec2 _position;
    };
    
}//end namespace objects

#endif