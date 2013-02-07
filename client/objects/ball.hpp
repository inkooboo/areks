#ifndef _AREKS_BALL_HPP_
# define _AREKS_BALL_HPP_

# include "defs.hpp"

# include "primitives.hpp"
# include "base_object.hpp"
# include "body_definitions.hpp"

namespace objects
{

    class Ball : public BaseObject
    {
    public:
        Ball(const Json::Value &description);
        ~Ball();

        virtual void draw() override;

        virtual void updateState( float t ) override;

        virtual b2Body* getBody() override;

        virtual pr::Vec2 getPosition() const override;

    private:

        BodyOwner _body;
        cc::CCSprite* _sprite;
    };

}//end namespace objects


#endif