#include "ball.hpp"

#include "master.hpp"
#include "physics.hpp"
#include "view.hpp"

#include "body_definitions.hpp"

namespace objects
{

        Ball::Ball(const Json::Value &description)
            : BaseObject(description)
        {
            const Json::Value pos_descr = description["position"];
            pr::Vec2 position(pos_descr.get("x", 0.f).asFloat(), pos_descr.get("y", 0.f).asFloat());

            //
            //init physics
            //
            defs::dyn::OneShapeDef def;
            def.setPosition( position.tob2Vec2() );
            def.setUserData( (void*)this );
            def.setShapeBox( 0.5, 0.5 );
            def.setDensity( 1 );
            def.setFriction( 0.9f );
            def.setRestitution( 0.3f );
			def.setFilterCategory( filter::OBJECTS );
			def.setFilterMask( filter::ALL );

            _body = master_t::subsystem<Physics>().CreateBody( def );

            //
            //init view
            //
            unsigned char color[] = {255, 0, 0};
            cc::CCTexture2D* texture = new cc::CCTexture2D();
            texture->autorelease();
            texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, pr::Vec2(1, 1).toCCSize() );
            _sprite = cc::CCSprite::create( texture );
            
            master_t::subsystem<View>().addSprite(_sprite);
            draw();
        }

        Ball::~Ball()
        {
            master_t::subsystem<View>().removeSprite(_sprite);
            //releaseJoints( _body.get() );
        }

        void Ball::draw()
        {
			master_t::subsystem<View>().drawSpriteHelper( _sprite, pr::Vec2( _body->GetPosition() ), _body->GetAngle() );
        }

        void Ball::updateState( float t )
        {
        }

        b2Body* Ball::getBody()
        {
            return _body.get();
        }

        pr::Vec2 Ball::getPosition() const
        {
            return pr::Vec2(_body->GetPosition());
        }

}//end namespace objects
