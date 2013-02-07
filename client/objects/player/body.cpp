#include "body.hpp"

#include "master.hpp"
#include "physics.hpp"

#include "view.hpp"

namespace objects
{

    namespace player
    {
    
        Body* Body::create( pr::Vec2 const& position )
        {
            return new Body( position );
        }
        
        Body::Body( pr::Vec2 const& position )
            : BaseObject(Json::Value())
        {
            static const pr::Vec2 size = pr::Vec2( 1.5f, 1.5f );
            //
            //init physics
            //
            defs::dyn::OneShapeDef def;
            def.setPosition( position.tob2Vec2() );
            def.setUserData( (void*)this );
            def.setShapeBox( size.x/2, size.y/2 );
            def.setDensity( 1 );
            def.setFriction( 0.2f );
            def.setRestitution( 0.7f );
            def.setFilterGroup( group::PLAYER );
			def.setFilterCategory( filter::OBJECTS );
			def.setFilterMask( filter::ALL );

            _body = master_t::subsystem<Physics>().CreateBody( def );

            //
            //init view
            //
            unsigned char color[] = {0, 255, 0};
            cc::CCTexture2D* texture = new cc::CCTexture2D();
            texture->autorelease();
            texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, size.toCCSize() );
            _sprite = cc::CCSprite::create( texture );
            
            draw();

            master_t::subsystem<View>().addSprite(_sprite);
        }
        
        Body::~Body()
        {
            master_t::subsystem<View>().removeSprite(_sprite);
        }
        
        void Body::draw()
        {
            master_t::subsystem<View>().drawSpriteHelper( _sprite, pr::Vec2( _body->GetPosition() ), _body->GetAngle() );
        }

        void Body::updateState( float t )
        {
        }

        b2Body* Body::getBody()
        {
            return _body.get();
        }

        pr::Vec2 Body::getPosition() const
        {
            return pr::Vec2( _body->GetPosition() );
        }
        
    }//end namespace player

}//end namespace objects