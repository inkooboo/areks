#ifndef _AREKS_PLAYER_HEAD_HPP_
#define _AREKS_PLAYER_HEAD_HPP_

#include "defs.hpp"
#include "primitives.hpp"
#include "body_definitions.hpp"
#include "objects/base_object.hpp"

namespace objects
{

    namespace player
    {
    
        class Head : public BaseObject
        {
        public:
            enum State
            {
                REST = 0,
                FLY,
                RETURN,
                HOOK,

				UNKNOWN
            };

        public:
            static Head* create( pr::Vec2 const& position );
            static Head* create();

            ~Head();
            
            virtual void draw() override;

            virtual void updateState( float t ) override;

            virtual b2Body* getBody() override;
            
            virtual void collide( BaseObject* other, b2Contact *contact ) override;

            virtual pr::Vec2 getPosition() const override;
            
            void fly( pr::Vec2 const& point );
			void return_home();

            size_t getState() const;
            
        private:
            Head( pr::Vec2 const& position );

            void attachToBody();

            //don't use reference for point because lazy execute this function
			void hook(BaseObject* obj, pr::Vec2 point);
			void unhook();

			void setCollideNormal();
			void setCollideNone();
            
            State _state;
            pr::Vec2 _target_vec;
            
            BodyOwner _body;
            cc::CCSprite* _sprite;

			b2Joint* _attach_joint;
			b2RevoluteJointDef _attach_joint_def;
        };
        
    }//end namespace player

}//end namespace objects

#endif