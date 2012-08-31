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
        : m_animation("test")
    {
        pr::Vec2 size = pr::Vec2(m_animation.sprite()->getContentSize());
        
        //
        //init physics
        //
        defs::dyn::OneShapeDef def;
        def.setPosition( position.tob2Vec2() );
        def.setUserData( (void*)this );
        def.setShapeBox( size.x / 2, size.y / 2 );
        def.setDensity( 1 );
        def.setFriction( 0.2f );
        def.setRestitution( 0.7f );
		def.setFilterCategory( filter::OBJECTS );
		def.setFilterMask( filter::ALL );
        
        _body = master_t::subsystem<Physics>().CreateBody( def );
        
        //
        //init view
        //

        addSprite(m_animation.sprite());
        draw();
        
        m_state = STAY;
        m_animation.animate("stay", std::bind(&Enemy::brain_xD, this));
    }
    
    void Enemy::brain_xD()
    {
        if (m_state == STAY)
        {
            _body->ApplyForceToCenter(b2Vec2(-2500.f, 100.0f));
            m_animation.animate("move", std::bind(&Enemy::brain_xD, this));
            m_state = MOVE_LEFT;
            return;
        }
        if (m_state == MOVE_LEFT)
        {
            _body->ApplyForceToCenter(b2Vec2(2500.f, 100.0f));
            m_animation.animate("move", std::bind(&Enemy::brain_xD, this));
            m_state = MOVE_RIGHT;
            m_animation.sprite()->setFlipX(true);
            return;
        }
        if (m_state == MOVE_RIGHT)
        {
            m_animation.animate("stay", std::bind(&Enemy::brain_xD, this));
            m_state = STAY;
            m_animation.sprite()->setFlipX(false);
            return;
        }
    }
    
    Enemy::~Enemy()
    {
        removeSprite(m_animation.sprite());
        releaseJoints( _body.get() );
    }
    
    void Enemy::draw()
    {
        drawSpriteHelper( m_animation.sprite(), pr::Vec2( _body->GetPosition() ), _body->GetAngle() );
    }
    
    void Enemy::updateState( float t )
    {
    }

    b2Body * Enemy::getBody()
    {
        return _body.get();
    }
    

    pr::Vec2 Enemy::getPosition() const
    {
        return pr::Vec2();
    }
    
}//end namespace objects
