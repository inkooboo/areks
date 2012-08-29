#ifndef _AREKS_OBJECT_PLATFORM_HPP_
#define _AREKS_OBJECT_PLATFORM_HPP_

#include "defs.hpp"
#include "object_interfaces.hpp"

#include "primitives.hpp"
#include "body_definitions.hpp"

#include <vector>

namespace objects
{

    class Platform : public StaticObject
    {
    public:
        static Platform* create(std::vector<pr::Vec2> const& vertices);
        
        virtual void draw() override;

        virtual b2Body* getBody() override;
        
    private:
        Platform(std::vector<pr::Vec2> const& vertices);
        ~Platform();

        BodyOwner _body;
        cc::CCNode* _sprite;
		std::vector<cc::CCSprite*> _sprites;
		pr::Vec2 _center;
    };
    
}//end namespace objects

#endif