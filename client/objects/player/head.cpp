#include "head.hpp"

#include "master.hpp"
#include "player.hpp"
#include "physics.hpp"
#include "loop.hpp"
#include "view.hpp"

#include "body.hpp"
#include "objects/base_object.hpp"

static const float HEAD_SPEED = 30.f;
static const float RETURN_ACCURACY = 0.5f;

namespace objects
{

    namespace player
    {
    
        Head* Head::create( pr::Vec2 const& position )
        {
            return new Head( position );
        }

        Head* Head::create()
        {
            std::shared_ptr<BaseObject> body = master_t::subsystem<Player>().getBody();
            return new Head( body->getPosition() );
        }
        
        Head::Head( pr::Vec2 const& position )
            : BaseObject(Json::Value())
            , _state( REST )
			, _attach_joint(0)
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

            master_t::subsystem<View>().addSprite(_sprite);

			//
			//extend init
			//
			setCollideNone();
			attachToBody();
        }
        
        Head::~Head()
        {
            master_t::subsystem<View>().removeSprite(_sprite);
        }
        
        void Head::draw()
        {
            master_t::subsystem<View>().drawSpriteHelper( _sprite, pr::Vec2( _body->GetPosition() ), _body->GetAngle() );
        }

        void Head::updateState( float t )
        {
            switch( _state )
            {
                case REST:
                {
                    break;
                }
                case FLY:
                {
                    std::shared_ptr<BaseObject> obj = master_t::subsystem<Player>().getBody();
                    float dis = pr::distance( pr::Vec2(_body->GetPosition()), obj->getPosition() );
                    if( dis >= master_t::subsystem<Player>().getNeckMaxLength() )
                    {
                        return_home();
                    }
                    else
                    {
                        _body->SetLinearVelocity( _target_vec.tob2Vec2() );
                    }
                    break;
                }
                case RETURN:
                {
                    std::shared_ptr<BaseObject> obj = master_t::subsystem<Player>().getBody();
                    pr::Vec2 home_pos = obj->getPosition();
                    pr::Vec2 self_pos = pr::Vec2(_body->GetPosition());
                    float dis = pr::distance( home_pos, self_pos );
                    dis = (dis > 0) ? dis : -dis;
                    if( dis < RETURN_ACCURACY )
                    {
                        _state = REST;
                        _body->SetLinearVelocity( b2Vec2(0,0) );
                        _body->SetTransform( home_pos.tob2Vec2(), 0.f ); //FIXME very, VERY dangerous. It breaks all associated joint
						attachToBody();
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
			assert( _state == REST && "Head can fly only from REST!" );
			master_t::subsystem<Physics>().worldEngine()->DestroyJoint( _attach_joint );
			_attach_joint = 0;

            _state = FLY;
            _target_vec = point - pr::Vec2(_body->GetPosition());
            _target_vec = _target_vec.normalize();
            _target_vec *= HEAD_SPEED;
            _body->SetLinearVelocity( _target_vec.tob2Vec2() );

			setCollideNormal();
        }

		void Head::return_home()
		{
			if( _state == HOOK )
			{
				unhook();
			}

			_state = RETURN;
			setCollideNone();
			updateState(0.f);
		}
        
        void Head::collide( BaseObject* other, b2Contact *contact )
        {
			b2WorldManifold m;
			contact->GetWorldManifold( &m );
			pr::Vec2 p(m.points[0]);
			master_t::subsystem<Physics>().execute_after_step( std::bind(&Head::hook, this, other, p) );
        }

        pr::Vec2 Head::getPosition() const
        {
            return pr::Vec2( _body->GetPosition() );
        }

        size_t Head::getState() const
        {
            return _state;
        }

        void Head::attachToBody()
        {
			_attach_joint_def.Initialize( _body.get(), master_t::subsystem<Player>().getBody()->getBody(), _body->GetPosition() );
			_attach_joint = master_t::subsystem<Physics>().worldEngine()->CreateJoint( &_attach_joint_def );
        }

		void Head::setCollideNormal()
		{	
			b2Filter filter;
			filter.groupIndex = group::PLAYER;
			filter.categoryBits = filter::OBJECTS;
			filter.maskBits = filter::ALL;
			_body->GetFixtureList()->SetFilterData(filter);
		}

		void Head::setCollideNone()
		{
			b2Filter filter;
			filter.groupIndex = group::PLAYER;
			filter.categoryBits = filter::NONE;
			filter.maskBits = filter::NONE;
			_body->GetFixtureList()->SetFilterData(filter);
		}

        //don't use reference for point because lazy execute this function
		void Head::hook(BaseObject* obj, pr::Vec2 point)
		{
			// Head::hook can called several times because collide can happen several times withing one physic step
			//assert( _state != HOOK && "State already HOOK!" );
			if( _state != HOOK )
			{
				_state = HOOK;
				setCollideNone();
				_attach_joint_def.Initialize( _body.get(), obj->getBody(), point.tob2Vec2() );

				_attach_joint = master_t::subsystem<Physics>().worldEngine()->CreateJoint( &_attach_joint_def );
				master_t::subsystem<Player>().createNeck();
				//_attach_joint = master_t::subsystem<Physics>().worldEngine()->CreateJoint( &_attach_joint_def );
			}
		}

		void Head::unhook()
		{
			assert( _state == HOOK && "State don't HOOK!" );
            _state = UNKNOWN;
			master_t::subsystem<Physics>().worldEngine()->DestroyJoint( _attach_joint );
			_attach_joint = 0;
		}

        
    }//end namespace player

}//end namespace objects