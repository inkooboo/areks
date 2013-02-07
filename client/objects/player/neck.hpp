#ifndef _AREKS_PLAYER_NECK_HPP_
#define _AREKS_PLAYER_NECK_HPP_

#include "defs.hpp"
#include "objects/base_object.hpp"
#include "primitives.hpp"
#include "body_definitions.hpp"

#include <vector>

namespace objects
{

    namespace player
    {
    
        class Neck : public BaseObject
		{
		public:
			static Neck* create( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );
			static Neck* create( pr::Vec2 const& a_point, BaseObject* a_body, pr::Vec2 const& b_point, BaseObject* b_body );

			virtual void draw() override;

			virtual void updateState( float t ) override;

			virtual b2Body* getBody() override;

			virtual void deleteJoint( b2Joint* joint ) override;

			virtual pr::Vec2 getPosition() const override;

			~Neck();

			float getTension();

			void shorten(float length);			

		private:
			Neck( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );

			std::vector<b2Body*> _sticks_bodies;
			std::vector<cc::CCSprite*> _sticks_sprites;

			std::vector<b2RevoluteJoint*> _revolute_joints;
			std::vector<b2DistanceJoint*> _distance_joints;
			std::vector<cc::CCSprite*> _connections_sprites;

			b2RevoluteJointDef _revolute_def;
			b2DistanceJointDef _distance_def;
		};
        
    }//end namespace player

}//end namespace objects

#endif