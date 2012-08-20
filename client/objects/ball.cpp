#include "ball.hpp"

#include "master.hpp"
#include "physics.hpp"
#include "view.hpp"

namespace objects
{

        Ball* Ball::create( pr::Vec2 const& position )
        {
            return new Ball( position );
        }

        Ball::Ball( pr::Vec2 const& position )
        {
            //
            //init physics
            //
            b2BodyDef body_def;
            body_def.type = b2_dynamicBody;
            body_def.position = position.tob2Vec2();
            body_def.userData = (void*)this;

            //b2CircleShape shape;
            //shape.m_radius = 3;
            b2PolygonShape shape;
            shape.SetAsBox( 0.5, 0.5 );

            b2FixtureDef fixture_def;
            fixture_def.shape = &shape;
            fixture_def.density = 1;
            fixture_def.friction = (float)0.2;
            fixture_def.restitution = (float)0.7;

            _body = master_t::subsystem<Physics>().worldEngine()->CreateBody( &body_def );
            _body->CreateFixture( &fixture_def );

            //
            //init view
            //
            unsigned char color[] = {150, 150, 150};
            cc::CCTexture2D* texture = new cc::CCTexture2D();
            //texture->autorelease();
            texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, pr::Vec2(1, 1).toCCSize() );
            _sprite = cc::CCSprite::create( texture );

            draw();

            master_t::subsystem<View>().gameLayer()->addChild( _sprite );
        }

        Ball::~Ball()
        {
            _sprite->removeFromParentAndCleanup( true );
            _sprite->release();
            release_joints( _body );
            master_t::subsystem<Physics>().worldEngine()->DestroyBody( _body );
        }

        void Ball::draw()
        {
            //angle = 0, circle don't need it =)
            draw_sprite_helper( _sprite, pr::Vec2( _body->GetPosition() ), 0 );
        }

        void Ball::updateState( float t )
        {
        }

        b2Body* Ball::getBody()
        {
            return _body;
        }

}//end namespace objects