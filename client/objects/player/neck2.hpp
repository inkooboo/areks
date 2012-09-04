#ifndef _AREKS_PLAYER_NECK2_HPP_
#define _AREKS_PLAYER_NECK2_HPP_

#include "defs.hpp"
#include "objects/object_interfaces.hpp"
#include "primitives.hpp"
#include "body_definitions.hpp"

#include <vector>

namespace objects
{

    namespace player
    {
		class Head;
		class Body;
    
        class Neck2 : public DynamicObject
		{
		public:
			static Neck2* create( pr::Vec2 const& a_point, objects::player::Body* body, pr::Vec2 const& b_point, objects::player::Head* head );

			virtual void draw() override;

			virtual void updateState( float t ) override;

			virtual b2Body* getBody() override;

			virtual pr::Vec2 getPosition() const override;

			~Neck2();

			void shorten();			

		private:
			Neck2( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );

			std::vector<b2Body*> _sticks_bodies;
			std::vector<cc::CCSprite*> _sticks_sprites;

			std::vector<b2DistanceJoint*> _distance_joints;

			b2DistanceJointDef _distance_def;
		};
        
    }//end namespace player

}//end namespace objects

#endif