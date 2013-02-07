#ifndef _AREKS_PLAYER_NECK2_HPP_
#define _AREKS_PLAYER_NECK2_HPP_

#include "defs.hpp"
#include "objects/base_object.hpp"
#include "primitives.hpp"
#include "body_definitions.hpp"

#include <vector>
#include <memory>

namespace objects
{

    namespace player
    {
		class Head;
		class Body;
    
        class Neck2 : public BaseObject
		{
		public:
			static Neck2* create( pr::Vec2 const& a_point, std::shared_ptr<objects::player::Body> body, pr::Vec2 const& b_point, std::shared_ptr<objects::player::Head> head );

			virtual void draw() override;

			virtual void updateState( float t ) override;

			virtual b2Body* getBody() override;

			virtual pr::Vec2 getPosition() const override;

			~Neck2();

			void shorten();
			void extend();

			float getCurrentLength() const;

		private:
			Neck2( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );

			std::vector<b2Body*> _sticks_bodies;
			std::vector<cc::CCSprite*> _sticks_sprites;

			std::vector<b2DistanceJoint*> _distance_joints;

			b2BodyDef _stick_def;
			b2FixtureDef _stick_fixture_def;
			b2CircleShape _stick_shape;
			b2DistanceJointDef _distance_def;
			cc::CCTexture2D* _stick_tex;
		};
        
    }//end namespace player

}//end namespace objects

#endif