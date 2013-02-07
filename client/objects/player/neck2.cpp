#include "neck2.hpp"

#include "master.hpp"
#include <math.h>

#include "physics.hpp"
#include "view.hpp"
#include "player.hpp"

#include "head.hpp"
#include "body.hpp"

#define NECK2_STICK_RADIUS 0.20f
#define NECK2_STICK_DIAMETER (2 * NECK2_STICK_RADIUS)
//ROPE_DENSITY - mass of rope
#define NECK2_DENSITY 1.0f
#define NECK2_FRICTION (float)0.0f


namespace objects
{

    namespace player
    {
    
		Neck2* Neck2::create( pr::Vec2 const& a_point, std::shared_ptr<objects::player::Body> body, pr::Vec2 const& b_point, std::shared_ptr<objects::player::Head> head )
		{
			return new Neck2( a_point, body->getBody(), b_point, head->getBody() );
		}

		Neck2::Neck2( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body )
            : BaseObject(Json::Value())
		{
			float distance = pr::distance( a_point, b_point );

			//
			//init physics
			//

			size_t stick_count = size_t(distance/NECK2_STICK_DIAMETER);

			//minimum stick count = 1
			if(stick_count == 0)
			{
				stick_count = 1;
			}

			//prepare rope sticks

			//prepare sticks body definition
			_stick_def.type = b2_dynamicBody;
			_stick_def.userData = (void*)this;                                              
			_stick_def.linearDamping = 0;

			b2Body* cur_body;
			b2Body* prev_body;

			//prepare sticks shape definition
			_stick_shape.m_radius = NECK2_STICK_RADIUS;

			//prepare distance joint definition
			_distance_def.collideConnected = false;
			_distance_def.dampingRatio = 0;

			//prepare fixtures definition
			_stick_fixture_def.friction = NECK2_FRICTION;
			_stick_fixture_def.density = NECK2_DENSITY;
			_stick_fixture_def.shape = &_stick_shape;
			_stick_fixture_def.filter.categoryBits = filter::NECK;
			_stick_fixture_def.filter.maskBits = filter::PLATFORMS;

			//calculate dx and dy for sticks
				//calculate angle of sticks
			pr::Vec2 v = a_point - b_point;
			float angle = pr::angleAxisX( v );
			float dx = -NECK2_STICK_DIAMETER * cos( angle ); //FIXME what's the minus?
			float dy = -NECK2_STICK_DIAMETER * sin( angle ); //FIXME what's the minus?

			//create rope sticks
			b2World* worldEngine = master_t::subsystem<Physics>().worldEngine();
			prev_body = a_body;
			for( size_t i = 0; i<stick_count; ++i )
			{
				_stick_def.position = b2Vec2( a_point.x + dx*i + dx/2, a_point.y + dy*i + dy/2);
				cur_body = worldEngine->CreateBody( &_stick_def );
				_sticks_bodies.push_back( cur_body );
				cur_body->CreateFixture( &_stick_fixture_def );

				_distance_def.Initialize( prev_body, cur_body, prev_body->GetPosition(), cur_body->GetPosition() );
				_distance_joints.push_back( static_cast<b2DistanceJoint*>(worldEngine->CreateJoint( &_distance_def )) );

				prev_body = cur_body;                        
			}

			_distance_def.Initialize( prev_body, b_body, prev_body->GetPosition(), b_body->GetPosition() );
			_distance_def.length = NECK2_STICK_RADIUS;
			_distance_joints.push_back( static_cast<b2DistanceJoint*>(worldEngine->CreateJoint( &_distance_def )) );

			//
			//init view
			//
			unsigned char color[] = {100, 100, 100};
			_stick_tex = new cc::CCTexture2D();
			//_stick_tex->autorelease();

			_stick_tex->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, pr::Vec2(NECK2_STICK_DIAMETER, NECK2_STICK_DIAMETER).toCCSize() );

			for( auto it = _sticks_bodies.begin(), end = _sticks_bodies.end(); it!=end; ++it )
			{
				_sticks_sprites.push_back(cc::CCSprite::create( _stick_tex ));
			}


			for( auto it = _sticks_sprites.begin(), end = _sticks_sprites.end(); it!=end; ++it )
			{
				master_t::subsystem<View>().addSprite(*it);
			}

			draw();
		}

		void Neck2::draw()
		{
			for(size_t i=0; i<_sticks_bodies.size(); ++i)
			{
				master_t::subsystem<View>().drawSpriteHelper( _sticks_sprites[i], _sticks_bodies[i]->GetPosition(), 0.f );
			}
		}

		void Neck2::updateState( float t )
		{
		}

		Neck2::~Neck2()
		{
			for( auto it = _sticks_sprites.begin(), end = _sticks_sprites.end(); it!=end; ++it )
			{
				master_t::subsystem<View>().removeSprite(*it);
			}
			_stick_tex->release();

			for( auto it = _sticks_bodies.begin(), end = _sticks_bodies.end(); it!=end; ++it )
			{
				master_t::subsystem<Physics>().worldEngine()->DestroyBody(*it);
			}
		}

		b2Body* Neck2::getBody()
		{
			return 0;
		}

		pr::Vec2 Neck2::getPosition() const
		{
			return pr::Vec2(0,0);
		}

		void Neck2::shorten()
		{
			if( _sticks_bodies.size() > 1 )
			{
				//if too far from body to first stick then do nothing
				float distance = pr::distance( pr::Vec2(_distance_joints[0]->GetAnchorA()), pr::Vec2(_distance_joints[0]->GetAnchorB()) );
				if( distance > 2*NECK2_STICK_DIAMETER ) return;

				Physics& physics = master_t::subsystem<Physics>();

				physics.worldEngine()->DestroyBody( *(_sticks_bodies.begin()) );
				_sticks_bodies.erase( _sticks_bodies.begin() );


				master_t::subsystem<View>().removeSprite( *(_sticks_sprites.begin()) );
				_sticks_sprites.erase( _sticks_sprites.begin() );

				_distance_joints.erase( _distance_joints.begin() );

				b2Body* first_stick = *(_sticks_bodies.begin());
				b2Body* player_body = master_t::subsystem<Player>().getBody()->getBody();
				_distance_def.Initialize( player_body, first_stick, player_body->GetPosition(), first_stick->GetPosition() );
				_distance_def.length = NECK2_STICK_RADIUS;
				_distance_joints[0] = static_cast<b2DistanceJoint*>( physics.worldEngine()->CreateJoint( &_distance_def ) );

				//give some impulse to body to speed up shorten
				pr::Vec2 impulse = pr::Vec2(first_stick->GetPosition()) - pr::Vec2(player_body->GetPosition());
				impulse.normalize();
				impulse *= player_body->GetMass();
				player_body->ApplyLinearImpulse( impulse.tob2Vec2(), player_body->GetPosition() );
			}
		}

		void Neck2::extend()
		{
			if( master_t::subsystem<Player>().getNeckMaxLength() > getCurrentLength() )
			{
				Physics& physics = master_t::subsystem<Physics>();
				b2World* b2_world = physics.worldEngine();

				b2_world->DestroyJoint( _distance_joints[0] );

				b2Body* first_stick = *(_sticks_bodies.begin());
				b2Body* player_body = master_t::subsystem<Player>().getBody()->getBody();

				pr::Vec2 vector = pr::Vec2(player_body->GetPosition()) - pr::Vec2(first_stick->GetPosition());
				vector.normalize();
				vector *= NECK2_STICK_DIAMETER;
				_stick_def.position = ( pr::Vec2(first_stick->GetPosition()) + vector ).tob2Vec2();
				_sticks_bodies.insert( _sticks_bodies.begin(), b2_world->CreateBody(&_stick_def) );
				_sticks_bodies[0]->CreateFixture( &_stick_fixture_def );

				_sticks_sprites.insert( _sticks_sprites.begin(), cc::CCSprite::create(_stick_tex) );
				master_t::subsystem<View>().addSprite( _sticks_sprites[0] );
			
				_distance_def.Initialize( _sticks_bodies[0], _sticks_bodies[1], _sticks_bodies[0]->GetPosition(), _sticks_bodies[1]->GetPosition() );
				_distance_joints[0] = static_cast<b2DistanceJoint*>( b2_world->CreateJoint( &_distance_def ) );

				_distance_def.Initialize( player_body, _sticks_bodies[0], player_body->GetPosition(), _sticks_bodies[0]->GetPosition() );
				_distance_def.length = NECK2_STICK_RADIUS;
				_distance_joints.insert( _distance_joints.begin(), static_cast<b2DistanceJoint*>( b2_world->CreateJoint(&_distance_def) ) );

				//give some impulse to body to speed up extend
				pr::Vec2 impulse = vector;
				impulse.normalize();
				impulse *= 2* player_body->GetMass();
				player_body->ApplyLinearImpulse( impulse.tob2Vec2(), player_body->GetPosition() );
			}
		}

		float Neck2::getCurrentLength() const
		{
			return ( NECK2_STICK_DIAMETER * _sticks_bodies.size() );
		}

        
    }//end namespace player

}//end namespace objects