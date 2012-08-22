#ifndef _AREKS_BALL_HPP_
#define _AREKS_BALL_HPP_

#include "defs.hpp"

#include "primitives.hpp"
#include "object_interfaces.hpp"
#include "body_definitions.hpp"

namespace objects
{

    class Ball : public DynamicObject
    {
    public:
        static Ball* create( pr::Vec2 const& position );

        virtual void draw() override;

        virtual void updateState( float t ) override;

        virtual b2Body* getBody() override;

    private:
        Ball( pr::Vec2 const& position );
        ~Ball();

        BodyOwner _body;
        cc::CCSprite* _sprite;
    };

}//end namespace objects


#endif