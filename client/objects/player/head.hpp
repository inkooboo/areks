#ifndef _AREKS_PLAYER_HEAD_HPP_
#define _AREKS_PLAYER_HEAD_HPP_

#include "defs.hpp"
#include "../object_interfaces.hpp"
#include "primitives.hpp"
#include "body_definitions.hpp"

namespace objects
{

    namespace player
    {
    
        class Head : public DynamicObject
        {
        public:
            static Head* create( pr::Vec2 const& position );

            ~Head();
            
            virtual void draw() override;

            virtual void updateState( float t ) override;

            virtual b2Body* getBody() override;
            
            virtual void collide( BaseObject* other ) override;

            virtual pr::Vec2 getPosition() const override;
            
            void fly( pr::Vec2 const& point );
            
        private:
            Head( pr::Vec2 const& position );
            
            enum State
            {
                IMMOBILITY = 0,
                FLY,
                RETURN,
                HOOK
            };
            
            State _state;
            pr::Vec2 _target_vec;
            
            BodyOwner _body;
            cc::CCSprite* _sprite;
        };
        
    }//end namespace player

}//end namespace objects

#endif