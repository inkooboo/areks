#ifndef _AREKS_PLAYER_NECK_HPP_
#define _AREKS_PLAYER_NECK_HPP_

#include "defs.hpp"

#include "primitives.hpp"
#include "base_object.hpp"

#include <vector>

namespace objects
{

    class Rope : public BaseObject
    {
    public:
        Rope( pr::Vec2 const& a_point, BaseObject* a_body, pr::Vec2 const& b_point, BaseObject* b_body );
        Rope( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );
        ~Rope();

        virtual void draw() override;

        virtual void updateState( float t ) override;

        virtual b2Body* getBody() override;

        virtual void deleteJoint( b2Joint* joint ) override;

        virtual pr::Vec2 getPosition() const override;

    private:

        std::vector<b2Body*> _sticks_bodies;
        std::vector<cc::CCSprite*> _sticks_sprites;

        std::vector<b2Joint*> _connections_bodies;
        std::vector<cc::CCSprite*> _connections_sprites;
    };

}//end namespace objects


#endif