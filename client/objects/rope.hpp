#ifndef _AREKS_ROPE_HPP_
#define _AREKS_ROPE_HPP_

#include "defs.hpp"

#include "primitives.hpp"
#include "object_interfaces.hpp"

#include <vector>

namespace objects
{

    class Rope : public DynamicObject
    {
    public:
        static Rope* create( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );
        static Rope* create( pr::Vec2 const& a_point, BaseObject* a_body, pr::Vec2 const& b_point, BaseObject* b_body );

        virtual void draw() override;

        virtual void updateState( float t ) override;

        virtual b2Body* getBody() override;

        virtual void deleteJoint( b2Joint* joint ) override;

    private:
        Rope( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );
        ~Rope();

        std::vector<b2Body*> _sticks_bodies;
        std::vector<cc::CCSprite*> _sticks_sprites;

        std::vector<b2Joint*> _connections_bodies;
        std::vector<cc::CCSprite*> _connections_sprites;
    };

}//end namespace objects


#endif