#ifndef _AREKS_PLAYER_NECK_HPP_
#define _AREKS_PLAYER_NECK_HPP_

#include "defs.hpp"
#include "objects/object_interfaces.hpp"
#include "primitives.hpp"
#include "body_definitions.hpp"

#include <vector>

namespace objects
{

    namespace player
    {
    
        class Neck : public DynamicObject
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

		private:
			Neck( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body );

			std::vector<b2Body*> _sticks_bodies;
			std::vector<cc::CCSprite*> _sticks_sprites;

			std::vector<b2Joint*> _connections_bodies;
			std::vector<cc::CCSprite*> _connections_sprites;
		};
        
    }//end namespace player

}//end namespace objects

#endif