#ifndef _AREKS_PLAYER_BODY_HPP_
#define _AREKS_PLAYER_BODY_HPP_

#include "defs.hpp"
#include "primitives.hpp"
#include "objects/base_object.hpp"
#include "body_definitions.hpp"

namespace objects
{

    namespace player
    {
    
        class Body : public BaseObject
        {
        public:
            static Body* create( pr::Vec2 const& position );

            ~Body();
            
            virtual void draw() override;

            virtual void updateState( float t ) override;

            virtual b2Body* getBody() override;

            virtual pr::Vec2 getPosition() const override;
            
        private:
            Body( pr::Vec2 const& position );
            
            BodyOwner _body;
            cc::CCSprite* _sprite;
        };
        
    }//end namespace player

}//end namespace objects

#endif