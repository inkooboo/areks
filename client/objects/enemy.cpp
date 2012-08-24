//
//  enemy.cpp
//  areks
//
//  Created by inkooboo on 8/23/12.
//
//

#include "enemy.hpp"
#include "master.hpp"
#include "physics.hpp"
#include "view.hpp"

#include "body_definitions.hpp"

namespace objects
{
    
    Enemy * Enemy::create( pr::Vec2 const& position )
    {
        return new Enemy( position );
    }
    
    Enemy::Enemy( pr::Vec2 const& position )
    {
        //
        //init physics
        //
        defs::dyn::OneShapeDef def;
        def.setPosition( position.tob2Vec2() );
        def.setUserData( (void*)this );
        def.setShapeBox( 0.5, 0.5 );
        def.setDensity( 1 );
        def.setFriction( 0.2f );
        def.setRestitution( 0.7f );
        
        _body = master_t::subsystem<Physics>().CreateBody( def );
        
        //
        //init view
        //
//        unsigned char color[] = {150, 150, 150};
//        cc::CCTexture2D* texture = new cc::CCTexture2D();
//        texture->autorelease();
//        texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, pr::Vec2(1, 1).toCCSize() );
//        _sprite = cc::CCSprite::create( texture );
//        
//        addSprite(_sprite);
        draw();
    }
    
    Enemy::~Enemy()
    {
//        removeSprite(_sprite);
        releaseJoints( _body.get() );
    }
    
    void Enemy::draw()
    {
        //angle = 0, circle don't need it =)
//        drawSpriteHelper( _sprite, pr::Vec2( _body->GetPosition() ), 0 );
    }
    
    void Enemy::updateState( float t )
    {
    }
    
    b2Body * Enemy::getBody()
    {
        return _body.get();
    }
    
}//end namespace objects
