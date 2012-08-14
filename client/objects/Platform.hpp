#ifndef _AREKS_OBJECT_PLATFORM_HPP_
#define _AREKS_OBJECT_PLATFORM_HPP_

#include "defs.hpp"
#include "ObjectInterfaces.hpp"

#include "Primitives.hpp"

namespace objects
{

    class Platform : public StaticObject
    {
    public:
        static Platform* create(pr::Vec2 const& coordinates, pr::Vec2 const& size);

        ~Platform();
        
        virtual void draw() override;
        
    private:
        Platform(pr::Vec2 const& coordinates, pr::Vec2 const& size);

        b2Body* _body;
        cc::CCSprite* _sprite;
        pr::Vec2 _position;
    };
    
}//end namespace objects

#endif