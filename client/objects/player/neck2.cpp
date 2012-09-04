#include "neck2.hpp"

#include "master.hpp"
#include <math.h>

#include "physics.hpp"
#include "view.hpp"
#include "player.hpp"

#include "head.hpp"
#include "body.hpp"

#define NECK2_STICK_RADIUS 0.25f
#define NECK2_STICK_DIAMETER (2 * NECK2_STICK_RADIUS)
//ROPE_DENSITY - mass of rope
#define NECK2_DENSITY 1.0f
#define NECK2_FRICTION (float)0.0f


namespace objects
{

    namespace player
    {
    
		Neck2* Neck2::create( pr::Vec2 const& a_point, objects::player::Body* body, pr::Vec2 const& b_point, objects::player::Head* head )
		{
			return new Neck2( a_point, body->getBody(), b_point, head->getBody() );
		}

		Neck2::Neck2( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body )
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
			b2BodyDef body_def;
			body_def.type = b2_dynamicBody;
			body_def.userData = (void*)this;                                              

			b2Body* cur_body;
			b2Body* prev_body;

			//prepare sticks shape definition
			b2CircleShape stick_shape;
			stick_shape.m_radius = NECK2_STICK_RADIUS;

			//prepare distance joint definition
			_distance_def.collideConnected = false;
			_distance_def.dampingRatio = 0;

			//prepare fixtures definition
			b2FixtureDef fixture_def;
			fixture_def.friction = NECK2_FRICTION;
			fixture_def.density = NECK2_DENSITY;
			fixture_def.shape = &stick_shape;
			fixture_def.filter.categoryBits = filter::NECK;
			fixture_def.filter.maskBits = filter::PLATFORMS;

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
				body_def.position = b2Vec2( a_point.x + dx*i + dx/2, a_point.y + dy*i + dy/2);
				cur_body = worldEngine->CreateBody( &body_def );
				_sticks_bodies.push_back( cur_body );
				cur_body->CreateFixture( &fixture_def );

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
			cc::CCTexture2D* texture = new cc::CCTexture2D();
			texture->autorelease();
			texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, pr::Vec2(NECK2_STICK_DIAMETER, NECK2_STICK_DIAMETER).toCCSize() );

			for( auto it = _sticks_bodies.begin(), end = _sticks_bodies.end(); it!=end; ++it )
			{
				_sticks_sprites.push_back(cc::CCSprite::create( texture ));
			}


			for( auto it = _sticks_sprites.begin(), end = _sticks_sprites.end(); it!=end; ++it )
			{
				addSprite(*it);
			}

			draw();
		}

		void Neck2::draw()
		{
			for(size_t i=0; i<_sticks_bodies.size(); ++i)
			{
				drawSpriteHelper( _sticks_sprites[i], _sticks_bodies[i]->GetPosition(), _sticks_bodies[i]->GetAngle() );
			}
		}

		void Neck2::updateState( float t )
		{
		}

		Neck2::~Neck2()
		{
			for( auto it = _sticks_sprites.begin(), end = _sticks_sprites.end(); it!=end; ++it )
			{
				removeSprite(*it);
			}

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
				Physics& physics = master_t::subsystem<Physics>();

				physics.worldEngine()->DestroyBody( *(_sticks_bodies.begin()) );
				_sticks_bodies.erase( _sticks_bodies.begin() );

				removeSprite( *(_sticks_sprites.begin()) );
				_sticks_sprites.erase( _sticks_sprites.begin() );

				_distance_joints.erase( _distance_joints.begin() );

				b2Body* first_stick = *(_sticks_bodies.begin());
				b2Body* player_body = master_t::subsystem<Player>().getBody()->getBody();
				_distance_def.Initialize( player_body, first_stick, player_body->GetPosition(), first_stick->GetPosition() );
				_distance_def.length = NECK2_STICK_RADIUS;
				_distance_joints[0] = static_cast<b2DistanceJoint*>( physics.worldEngine()->CreateJoint( &_distance_def ) );
			}
		}

        
    }//end namespace player

}//end namespace objects