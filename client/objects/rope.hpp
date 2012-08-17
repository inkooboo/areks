#ifndef _AREKS_ROPE_HPP_
#define _AREKS_ROPE_HPP_

#include "defs.hpp"

#include "primitives.hpp"
#include "object_interfaces.hpp"

namespace objects
{
    namespace detail
    {
        class RopePoint
        {
        public:
            float x, y, old_x, old_y;

            void setPos(float new_x, float new_y);
            void update();
            void applyGravity(float dt);
        };

        class RopeStick
        {
        public:
            RopeStick(RopePoint* a, RopePoint* b);

            RopePoint *point_a;
	        RopePoint *point_b;
	        float hypotenuse;

            void contract();
        };
    }//end namespace detail

    class Rope : public DynamicObject
    {
    public:
        static Rope* create( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );

        virtual void draw() override;

        virtual void updateState( float t ) override;

    private:
        Rope( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );
        ~Rope();

        cc::CCSpriteBatchNode* _spriteSheet;
        b2Body* _a_body;
        b2Body* _b_body;
        pr::Vec2 _a_point;
        pr::Vec2 _b_point;
        size_t _num_points;
        float _anti_sag_hack;

        void reset();
    };

}//end namespace objects


#endif