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

namespace objects
{
        
    Enemy::Enemy(const Json::Value &description)
        : BaseObject(description)
        , m_animation("midget")
    {
        const Json::Value pos_descr = description["position"];
        pr::Vec2 position(pos_descr.get("x", 0.f).asFloat(), pos_descr.get("y", 0.f).asFloat());

        pr::Vec2 size = pr::Vec2(2,3.14);
        
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

        master_t::subsystem<View>().addSprite(m_animation.sprite());
        draw();
        
        m_state = STAY;
        m_animation.animate("stay", std::bind(&Enemy::brain_xD, this));
    }
    
    void Enemy::brain_xD()
    {
        switch (m_state)
        {
            case STAY:
                _body->ApplyForceToCenter(b2Vec2(-1500.f, 50.0f));
                m_animation.animate("move_left", std::bind(&Enemy::brain_xD, this));
                m_state = MOVE_LEFT;
                break;
            case MOVE_LEFT:
                m_animation.animate("hit_left", std::bind(&Enemy::brain_xD, this));
                m_state = HIT_LEFT;
                break;
            case HIT_LEFT:
                _body->ApplyForceToCenter(b2Vec2(1500.f, 50.0f));
                m_animation.animate("move_right", std::bind(&Enemy::brain_xD, this));
                m_state = MOVE_RIGHT;
                break;
            case MOVE_RIGHT:
                m_animation.animate("hit_right", std::bind(&Enemy::brain_xD, this));
                m_state = HIT_RIGHT;
                break;
            case HIT_RIGHT:
                m_animation.animate("stay", std::bind(&Enemy::brain_xD, this));
                m_state = STAY;
                break;
        }
    }
    
    Enemy::~Enemy()
    {
        master_t::subsystem<View>().removeSprite(m_animation.sprite());
        releaseJoints( _body.get() );
    }
    
    void Enemy::draw()
    {
        pr::Vec2 position(_body->GetPosition());
        master_t::subsystem<View>().drawSpriteHelper( m_animation.sprite(), position, _body->GetAngle() );
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
