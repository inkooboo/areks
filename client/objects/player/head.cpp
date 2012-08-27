#include "head.hpp"

#include "master.hpp"
#include "player.hpp"
#include "physics.hpp"

#include "body.hpp"

static const float HEAD_SPEED = 10.f;
static const float RETURN_ACCURACY = 0.1f;

namespace objects
{

    namespace player
    {
    
        Head* Head::create( pr::Vec2 const& position )
        {
            return new Head( position );
        }
        
        Head::Head( pr::Vec2 const& position )
            : _state( IMMOBILITY )
        {
            static const pr::Vec2 size = pr::Vec2( 0.4f, 0.4f );
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

            _body = master_t::subsystem<Physics>().CreateBody( def );

            //
            //init view
            //
            unsigned char color[] = {140, 55, 100};
            cc::CCTexture2D* texture = new cc::CCTexture2D();
            texture->autorelease();
            texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, size.toCCSize() );
            _sprite = cc::CCSprite::create( texture );
            
            draw();

            addSprite(_sprite);
        }
        
        Head::~Head()
        {
            removeSprite(_sprite);
        }
        
        void Head::draw()
        {
            drawSpriteHelper( _sprite, pr::Vec2( _body->GetPosition() ), _body->GetAngle() );
        }

        void Head::updateState( float t )
        {
            switch( _state )
            {
                case IMMOBILITY:
                {
                    break;
                }
                case FLY:
                {
                    DynamicObject* obj = master_t::subsystem<Player>().getBody();
                    float dis = pr::distance( pr::Vec2(_body->GetPosition()), obj->getPosition() );
                    if( dis >= master_t::subsystem<Player>().getNeckMaxLength() )
                    {
                        _state = RETURN;
                        updateState( t );
                    }
                    else
                    {
                    }
                    break;
                }
                case RETURN:
                {
                    DynamicObject* obj = master_t::subsystem<Player>().getBody();
                    pr::Vec2 home_pos = obj->getPosition();
                    pr::Vec2 self_pos = pr::Vec2(_body->GetPosition());
                    float dis = pr::distance( home_pos, self_pos );
                    dis = (dis > 0) ? dis : -dis;
                    if( dis < RETURN_ACCURACY )
                    {
                        _state = IMMOBILITY;
                        _body->SetLinearVelocity( b2Vec2(0,0) );
                        _body->SetTransform( home_pos.tob2Vec2(), 0.f ); //FIXME very, VERY dangerous. It breaks all associated joint
                    }
                    else
                    {
                        pr::Vec2 home_vec = home_pos - pr::Vec2( _body->GetPosition() );
                        home_vec.normalize();
                        home_vec*=HEAD_SPEED;
                        _body->SetLinearVelocity( home_vec.tob2Vec2() );
                    }
                    
                    break;
                }
                case HOOK:
                {
                    break;
                }
                default: assert( false && "Unknown state of player head!");
            }
        }

        b2Body* Head::getBody()
        {
            return _body.get();
        }
        
        void Head::fly( pr::Vec2 const& point )
        {
            _state = FLY;
            _target_vec = point - pr::Vec2(_body->GetPosition());
            _target_vec = _target_vec.normalize();
            _target_vec *= HEAD_SPEED;
            _body->SetLinearVelocity( _target_vec.tob2Vec2() );
        }
        
        void Head::collide( BaseObject* other )
        {
            
        }

        pr::Vec2 Head::getPosition() const
        {
            return pr::Vec2( _body->GetPosition() );
        }
        
    }//end namespace player

}//end namespace objects